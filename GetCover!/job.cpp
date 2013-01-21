#pragma warning(disable:4996)
#include "stdafx.h"
#include "md5.h"
#include "markupstl.h"
#include "utf8.h"
#include "define.h"
#include "resource.h"
#include "job.h"

using namespace util::utf8;

CCriticalSection g_job_access;
CCriticalSection j_submit;
BOOL g_bCloseApp;
CEvent g_JobEvent;

#define LOCK_AS_SEMAPHORE 1

CEvent j_CopyJobEvent(FALSE, TRUE);
CSemaphore j_DownloadControl(5,5);
#ifndef LOCK_AS_SEMAPHORE
CSingleLock j_l(&j_DownloadControl);
#endif
BOOL j_SearchInProgress = FALSE;
LONG j_DownloadInProgress;

void SubmitProgress(CJob* job, TCHAR* format, ...);

static unsigned _stdcall ProcessJob(void * parameter);
int DownloadData(CJob* job, CByteArray &data, DWORD *dwDataSize);
int ProcessData(CJob* job, CByteArray &data, DWORD dwDataSize);

int ProcessDataCover(CJob* job, CByteArray &data, DWORD dwDataSize);
int ProcessDataFile(CJob* job, CByteArray &data, DWORD dwDataSize);
int ProcessDataSearch(CJob* job, CByteArray &data, DWORD dwDataSize);
int ProcessDataThumb(CJob* job, CByteArray &data, DWORD dwDataSize);

CString hrFileSize(int filesize)
{
	CString fs;
	double a = filesize;
	CString b = _TEXT("");

	if(a >=1000)
	{
		a/=1024;
		b = _TEXT("kB");
		if(a >=1000)
		{
			a/=1024;
			b = _TEXT("MB");
			if(a >=1000)
			{
				a/=1024;
				b = _TEXT("GB");
			}
		}
	}

	fs.Format(_TEXT("%.1f %s"), a, b);

	return fs;
}

unsigned _stdcall JobPool(void * parameter)
{
	g_JobEvent.ResetEvent();
	CJobs* jobs = (CJobs*) parameter;
	CJob job;

	j_DownloadInProgress = 0;

	while(g_bCloseApp == FALSE)
	{
		while(jobs->GetSize() == 0 && g_bCloseApp == FALSE) {}
		if(g_bCloseApp) break;

		g_job_access.Lock();
		job = jobs->GetAt(0);
		jobs->RemoveAt(0);
		g_job_access.Unlock();

		if(job.nJob == JOB_SEARCH && j_SearchInProgress)
		{
			MessageBox(job.hWnd, _TEXT("You have another search in progress.\nPlease wait untill it's finished"), _TEXT("Warning"), MB_OK | MB_ICONWARNING);
			continue;
		}

		unsigned int IDThread;
		j_CopyJobEvent.ResetEvent();
		TRACE(_TEXT("Job control waits for a free download slot\n"));
		::WaitForSingleObject(j_DownloadControl.m_hObject, INFINITE);
		TRACE(_TEXT("Job control waits for a search to complete (if any)\n"));
		while(j_SearchInProgress) {};
		if(job.nJob == JOB_SEARCH)
		{
			TRACE(_TEXT("Job control waits for all downloads to complete, since there's a search request\n"));
			while(j_DownloadInProgress >0) {};
		}
		TRACE(_TEXT("Job tries to lock a slot\n"));
#ifdef LOCK_AS_SEMAPHORE
		j_DownloadControl.Lock();
#else
		j_l.Lock();
#endif
		TRACE(_TEXT("Job control locks a slot\n"));
		if(job.nJob == JOB_SEARCH) j_SearchInProgress = TRUE;
		if(job.nJob == JOB_COVER || job.nJob == JOB_THUMB) ::InterlockedIncrement(&j_DownloadInProgress);
		TRACE(_TEXT("Job control starts a network thread\n"));
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcessJob, (void*) &job, 0, &IDThread);
		if(hThread <= 0)
		{
#ifdef LOCK_AS_SEMAPHORE
		j_DownloadControl.Unlock();
#else
		j_l.Unlock();
#endif
			MessageBox(job.hWnd, _TEXT("Cannot run selected task. Thread spawing error"), _TEXT("Warning"), MB_OK | MB_ICONWARNING);
		}
		TRACE(_TEXT("Job control waits for a job copy event to be set\n"));
		::WaitForSingleObject(j_CopyJobEvent.m_hObject, INFINITE);
		VERIFY(CloseHandle(hThread));
		
	};

	TRACE("Trying to cancel process thread\n");
	while(j_DownloadInProgress >0 || j_SearchInProgress) {};
	TRACE("Job thread done\n");
	g_JobEvent.SetEvent();

	return 0;
}

unsigned _stdcall ProcessJob(void * parameter)
{
	TRACE(_TEXT("Process job started\n"));
	CJob job = *((CJob*)parameter);
	TRACE(_TEXT("Process copied a job\n"));
	j_CopyJobEvent.SetEvent();

	CByteArray data;
	DWORD dwDataSize;
	int ret = 1;
	if(g_bCloseApp == FALSE)
	{
		if(DownloadData(&job, data, &dwDataSize) == 0)
		{
			if(dwDataSize > 0 && g_bCloseApp == FALSE)
			{
				ret = ProcessData(&job, data, dwDataSize);
				::SendMessage(job.hWnd, job.msg, 0, 0);
			}
		}
		else SubmitProgress(&job, _TEXT("Network error. Cannot download data."));
	}

	if(job.nJob == JOB_SEARCH) j_SearchInProgress = FALSE;
	if(job.nJob == JOB_COVER || job.nJob == JOB_THUMB) ::InterlockedDecrement(&j_DownloadInProgress);
	TRACE(_TEXT("Process job unlocks the slot [%d][%d][%d]\n"), j_SearchInProgress, j_DownloadInProgress, 0);
	
#ifdef LOCK_AS_SEMAPHORE
		j_DownloadControl.Unlock();
#else
		j_l.Unlock();
#endif

	return ret;
}

#define ERROR_CANNOT_OPEN_URL			20001;
#define ERROR_CANNOT_PREPARE_REQUEST	20002;

void SubmitProgress(CJob* job, TCHAR* format, ...)
{
	if(g_bCloseApp) return;
	j_submit.Lock();
    va_list args;
    int     len;
    TCHAR    *buffer;
    va_start( args, format );
    
    len = _vsctprintf( format, args ) +1;
    buffer = new TCHAR[len];
    _vstprintf( buffer, format, args );

	switch(job->nJob)
	{
	case JOB_COVER:
		if(job->pListCtrl == NULL) break;
		if(job->pListCtrl->GetSafeHwnd() == NULL) break;
		job->pListCtrl->SetItemText(job->nItem, SUBI_MESSAGE, buffer);
		break;
	case JOB_THUMB:
		if(job->pListCtrl == NULL) break;
		if(job->pListCtrl->GetSafeHwnd() == NULL) break;
		job->pListCtrl->SetItemText(job->nItem, SUBI_THUMB, buffer);
		break;
	case JOB_SEARCH:
		if(job->pInfo == NULL) break;
		if(job->pInfo->GetSafeHwnd() == NULL) break;
		job->pInfo->SetWindowText(buffer);
		break;
	}
    
	delete buffer;
	j_submit.Unlock();
}

int DownloadData(CJob* job, CByteArray &data, DWORD *dwDataSize)
{
	TRACE(_TEXT("Download data started\n"));
	data.RemoveAll();
	*dwDataSize = 0;
	CString host, object;
	INTERNET_PORT port;
	DWORD dwServiceType;
	AfxParseURL(job->sUrl, dwServiceType, host, object, port);
	if(dwServiceType != AFX_INET_SERVICE_HTTP) return 1;

	SubmitProgress(job, _TEXT(""));

	CInternetSession session (_TEXT("GetCover!/0.1"), 1, INTERNET_OPEN_TYPE_PRECONFIG , NULL, NULL, INTERNET_FLAG_DONT_CACHE);
	SubmitProgress(job, _TEXT("Initializing session"));
	TRACE("CInternetSession object initialized at 0x%08x\n", &session);
	CHttpFile* pFile = NULL;
	CHttpConnection* pServer = NULL;

	DWORD dwCFlags = INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD|INTERNET_FLAG_TRANSFER_BINARY;

	try {

		SubmitProgress(job, _TEXT("Connecting"));
		pServer = session.GetHttpConnection(host, dwCFlags, port);
		TRACE("CHttpConnection object initialized at 0x%08x\n", pServer);

		if(g_bCloseApp) TRACE(_TEXT("Download data cancelled\n"));
		if(g_bCloseApp) goto clean;

//		SubmitProgress(job, _TEXT("Connecting"));
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, object, NULL, 1, NULL, NULL, dwCFlags);
		TRACE("CHttpFile object initialized at 0x%08x\n", pFile);
		SubmitProgress(job, _TEXT("Sending request"));
		pFile->SendRequest();
		SubmitProgress(job, _TEXT("Request sent"));

		if(g_bCloseApp) TRACE(_TEXT("Download data cancelled\n"));
		if(g_bCloseApp) goto clean;

		DWORD dwCode;
		DWORD dwTotalSize = 0;
		pFile->QueryInfoStatusCode(dwCode);
		BOOL bSize = (pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, dwTotalSize) != 0);

		if(g_bCloseApp) TRACE(_TEXT("Download data cancelled\n"));
		if(g_bCloseApp) goto clean;
		SubmitProgress(job, _TEXT("Server response code: %d"), dwCode);

		if(dwCode == 200)
		{
			data.RemoveAll();
			BYTE szInetBuffer[BUFFER_SIZE];
			int nPos, nRead;
			DWORD dwRead = 0;
			do
			{
				memset(szInetBuffer, 0, BUFFER_SIZE);
				if(nRead = pFile->Read(szInetBuffer, BUFFER_SIZE))
				{

					if(g_bCloseApp) TRACE(_TEXT("Download data cancelled\n"));
					if(g_bCloseApp) goto clean;
					for(nPos = 0;nPos < nRead; nPos++)
						data.Add(szInetBuffer[nPos]);

				}
				dwRead += nRead;
				
				if(!bSize)
				{
					CString hrfs = hrFileSize(dwRead);
					SubmitProgress(job, _TEXT("Reading: %s"), hrfs );
				}
				else
				{
					SubmitProgress(job, _TEXT("Reading: %.1f%%"), 100.0*dwRead/dwTotalSize);
				}
			}while (nRead);

			*dwDataSize = dwRead;
		}
	}
	catch ( CInternetException* pEx )
	{
		TRACE(_TEXT("Download hit an exception\n"));
		TCHAR errorText[1000];
		pEx->GetErrorMessage(errorText, 1000);

		SubmitProgress(job, _TEXT("Network Error: %s"), errorText);

		pEx->Delete();
		if (pFile != NULL)
		{
			pFile->Close();
			delete pFile;
			TRACE("CHttpFile object closed at 0x%08x\n", pFile);
		}

		if (pServer != NULL)
		{
			pServer->Close();
			delete pServer;
			TRACE("CHttpConnection object closed at 0x%08x\n", pServer);
		}

		session.Close();
		TRACE("CInternetSession object closed at 0x%08x\n", &session);

		return 1;
	}

clean:
	TRACE("Download cleaning after ourselves\n", &session);

	if (pFile != NULL)
	{
		pFile->Close();
		delete pFile;
		TRACE("CHttpFile object closed at 0x%08x\n", pFile);
	}
	if (pServer != NULL)
	{
		pServer->Close();
		delete pServer;
		TRACE("CHttpConnection object closed at 0x%08x\n", pServer);
	}
	session.Close();
	TRACE("CInternetSession object closed at 0x%08x\n", &session);

	SubmitProgress(job, _TEXT("Complete"));

	TRACE(_TEXT("Download exit\n"));
	return 0;
}

int ProcessData(CJob* job, CByteArray &data, DWORD dwDataSize)
{
	switch(job->nJob)
	{
		case JOB_COVER:		return ProcessDataCover (job, data, dwDataSize);
		case JOB_THUMB:		return ProcessDataThumb (job, data, dwDataSize);
		case JOB_SEARCH:	return ProcessDataSearch(job, data, dwDataSize);
		default: return 1;
	}
}

int ProcessDataFile(CJob* job, CByteArray &data, DWORD dwDataSize)
{
	if(!job->sPath.IsEmpty())
	{
		MD5 context;
		context.update((unsigned char*) data.GetData(), (unsigned int)dwDataSize);
		context.finalize();
		char *s = context.hex_digest();
		BOOL bNotImage = (stricmp(s, AMAZON_NOT_AN_IMAGE) == 0);
		delete s;

		if(!bNotImage || job->nJob == JOB_THUMB)
		{
			CString csPath = job->sPath;

			CFile cfPic;
			CFileException ex;
			TCHAR error[1024];

			if(!cfPic.Open(csPath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoInherit | CFile::shareExclusive | CFile::typeBinary, &ex))
			{
				ex.GetErrorMessage(error, 1000);
				SubmitProgress(job, _TEXT("I/O Error: %s"), error);
			}
			else
			{
				try {
					TRACE(_TEXT("Saving thumb to [%s]\n"), csPath);
					cfPic.Write((unsigned char*) data.GetData(), (unsigned int)dwDataSize);

					if(job->nJob == JOB_COVER && job->nItem != -1)
					{
						job->pListCtrl->SetItemState(job->nItem, STATE_OK, LVIS_STATEIMAGEMASK);
						job->pListCtrl->SetItemText(job->nItem, SUBI_MESSAGE, _TEXT("Image downloaded"));
					}
				}
				catch( CFileException *pfEx ) {
					pfEx->GetErrorMessage(error, 1000);
					SubmitProgress(job, _TEXT("I/O Error: %s"), error);

					if(job->nJob == JOB_COVER && job->nItem != -1)
					{
						job->pListCtrl->SetItemState(job->nItem, STATE_ER, LVIS_STATEIMAGEMASK);
						job->pListCtrl->SetItemText(job->nItem, SUBI_MESSAGE, _TEXT("I/O Error while trying to save the cover"));
					}
				}
				cfPic.Close(); 
			}
		}
		else
		{
			if(job->nJob == JOB_COVER && job->nItem != -1)
			{
				job->pListCtrl->SetItemState(job->nItem, STATE_ER, LVIS_STATEIMAGEMASK);
				job->pListCtrl->SetItemText(job->nItem, SUBI_MESSAGE, _TEXT("Image doesn't exists on the server"));
			}
		}
	}

	return 0;
}

int ProcessDataCover(CJob* job, CByteArray &data, DWORD dwDataSize)
{
	return ProcessDataFile(job, data, dwDataSize);
}

int ProcessDataThumb(CJob* job, CByteArray &data, DWORD dwDataSize)
{
	return ProcessDataFile(job, data, dwDataSize);
}

int ProcessDataSearch(CJob* job, CByteArray &data, DWORD dwDataSize)
{
	if(job->nJob != JOB_SEARCH) return 1;

	CMarkupSTL xml;
	char* xml_raw = new char[dwDataSize + 1];
	memset(xml_raw, 0, dwDataSize + 1);
	strncpy(xml_raw, (char*)data.GetData(), dwDataSize);

	if (!xml.SetDoc(xml_raw))
	{
		delete xml_raw;
		CString error;
		tstring serror;
		assign_os_from_ansi(serror, xml.GetError().c_str());
		error.Format(_TEXT("Invalid server response.\n%s\nPlease try again"), serror.c_str());
		MessageBox(NULL, error, _TEXT("Error"), MB_OK | MB_ICONERROR);
		return 1;
	}

	delete xml_raw;

	if(xml.FindChildElem("error"))
	{
		tstring error;
		assign_os_from_ansi(error, xml.GetChildData().c_str());
		MessageBox(NULL, error.c_str(), _TEXT("Error"), MB_ICONERROR | MB_OK);
		return 1;
	}

	xml.FindChildElem("releases");
	xml.IntoElem();
	int nReleases = atoi(xml.GetAttrib("num").c_str());

	int nPos;

	tstring s_id, s_link, s_cover, s_artist, s_album, s_src, s_thumb, s_x, s_y, s_z;

	RELEASEDATA rd;

	DWORD_PTR nCounter = 0;

	while(nReleases && xml.FindChildElem("release"))
	{
		xml.IntoElem();
		assign_os_from_ansi(s_id, xml.GetAttrib("id").c_str());
		assign_os_from_ansi(s_src, xml.GetAttrib("src").c_str());

		xml.FindChildElem("link");
		assign_os_from_ansi(s_link, xml.GetChildData().c_str());

		xml.FindChildElem("cover");
		assign_os_from_ansi(s_cover, xml.GetChildData().c_str());

		xml.IntoElem();
		assign_os_from_ansi(s_x, xml.GetAttrib("width").c_str());
		assign_os_from_ansi(s_y, xml.GetAttrib("height").c_str());
		assign_os_from_ansi(s_z, xml.GetAttrib("size").c_str());
		xml.OutOfElem();

		xml.FindChildElem("thumbnail");
		assign_os_from_ansi(s_thumb, xml.GetChildData().c_str());

		xml.FindChildElem("artist");
		assign_os_from_ansi(s_artist, xml.GetChildData().c_str());
	
		xml.FindChildElem("album");
		assign_os_from_ansi(s_album, xml.GetChildData().c_str());

		rd.Set(s_src, s_id, s_link, s_cover, s_thumb, s_artist, s_album, s_x, s_y, s_z);
		rd.dwId = nCounter++;

		rd.nIcon = (int) job->pSrch->GetSize();

		for(nPos = 0; nPos < job->pSrch->GetSize(); nPos++)
		{
			if(rd.src.CompareNoCase(job->pSrch->GetAt(nPos).sParam) == 0)
				rd.nIcon = job->pSrch->GetAt(nPos).nIcon;
		}

		CString t_ar, t_al, t_th;
		md5(rd.md5, s_cover.c_str(), (int)s_cover.length());
		md5(t_ar, s_artist.c_str(), (int)s_artist.length());
		md5(t_al, s_album.c_str(), (int)s_album.length());
		md5(t_th, s_thumb.c_str(), (int)s_thumb.length());

		rd.md5_thumb = t_ar + _TEXT("_") + t_al + _TEXT("_") + t_th;
		rd.dwId = job->pRls->GetSize();

		job->pRls->Add(rd);

		xml.OutOfElem();
	}

	for(nPos = 0; nPos < job->pRls->GetSize(); nPos++)
	{
		job->pListCtrl->InsertItem(nPos, job->pRls->GetAt(nPos).link, job->pRls->GetAt(nPos).nIcon);
		job->pListCtrl->SetItemData(nPos, nPos);
		job->pListCtrl->SetItem(nPos, SUBI_ARTIST, LVIF_TEXT, job->pRls->GetAt(nPos).artist, 0, 0, 0, NULL);
		job->pListCtrl->SetItem(nPos, SUBI_ALBUM, LVIF_TEXT, job->pRls->GetAt(nPos).album,  0, 0, 0, NULL);
		job->pListCtrl->SetItem(nPos, SUBI_X, LVIF_TEXT, job->pRls->GetAt(nPos).x,  0, 0, 0, NULL);
		job->pListCtrl->SetItem(nPos, SUBI_Y, LVIF_TEXT, job->pRls->GetAt(nPos).y,  0, 0, 0, NULL);
		job->pListCtrl->SetItem(nPos, SUBI_FILESIZE, LVIF_TEXT, job->pRls->GetAt(nPos).filesize_fmt,  0, 0, 0, NULL);
	}

	return 0;
}

void md5(CString& buf, const TCHAR* data, int len)
{
	MD5 context;
	std::string text;
	assign_ansi_from_os(text, data);
	context.update((unsigned char*) text.c_str(), (unsigned int)len);
	context.finalize();
	char *s = context.hex_digest();
	tstring hash;
	assign_os_from_ansi(hash, s);
	buf = hash.c_str();
	delete s;
}

void md5_file(CString& file, CString &buf)
{
	MD5 context;
	FILE* f = _tfopen(file, _TEXT("rb"));
	if(f)
	{
		context.update(f);
		context.finalize();
		char *s = context.hex_digest();
		tstring hash;
		assign_os_from_ansi(hash, s);
		buf = hash.c_str();
		fclose(f);
		delete s;
	}
	else buf = _TEXT("");
}
