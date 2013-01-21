// GetCover!Dlg.cpp : implementation file
//
/*****************************/
//TODO
//+Синхронизация Search и Download
//-Lock!!
//-InitStates@OnBnClickedSearch
/*****************************/

#pragma warning(disable:4996)
#pragma comment(lib, "shlwapi")

#include "stdafx.h"
#include "define.h"
#include "job.h"|
#include "GetCover!.h"
#include "GetCover!Dlg.h"
#include "MP3FileInfo.h"
#include "utf8.h"

using namespace util::utf8;

#include <shellapi.h>

#include "download.h"
//#include "utf8.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define APP_FOLDER "Get Cover!"
#define THUMB_CACHE "ThumbCache"

#define THUMB_BORDER 2

#define NO_COVER "nocover.jpg"
#define LD_COVER "ldthumb.jpg"

#define ErrorBox(A) MessageBox(_TEXT(A), _TEXT("Error"), MB_ICONERROR|MB_OK)
#define UpdateIB	::SendMessage(thData->hWnd, WM_USER_UPDATE_INFO_BOX, 0, 0)
#define SetIB		::SendMessage(thData.hWnd, WM_USER_UPDATE_INFO_BOX, 0, 0)

//#define DEFAULT_COVERFILE _TEXT("folder.jpg")

#define LP_DOWNLOADLIST		101
#define LP_DOWNLOADCOVER	102
#define LP_DOWNLOADTHUMB	103

#define THUMWIDTH 100
#define THUMHEIGHT THUMWIDTH

#define WM_USER_DOWNLOAD_COMPLETE	WM_USER + 300
#define WM_USER_UPDATE_INFO_BOX		WM_USER + 301
#define WM_USER_THUMBDOWNLOADED		WM_USER + 302

static int WINAPI BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam, LPARAM lpData);

CJob::CJob()
{
	this->nJob = JOB_NONE;
	this->hWnd = NULL;
}

CJob::CJob(HWND hWnd, CString& sUrl, CListCtrl* pListCtrl, CEdit* pInfo, RLSARRAY* pRls, SRCHARRAY* pSrch, UINT msg, LPARAM lPAram, WPARAM wParam)
{
	this->hWnd = hWnd;
	this->nJob = JOB_SEARCH;
	this->pListCtrl = pListCtrl;
	this->pRls = pRls;
	this->pInfo = pInfo;
	this->pSrch = pSrch;
	this->msg = msg;
	this->sUrl = sUrl;
	this->lParam = lParam;
	this->wParam = wParam;
}

CJob::CJob(HWND hWnd, CString& sUrl, CListCtrl* pListCtrl, CString& sPath, UINT msg, int nItem, LPARAM lPAram, WPARAM wParam)
{
	this->nJob = JOB_NONE;
	this->hWnd = hWnd;
	this->nJob = nJob;
	this->nItem = nItem;
	this->msg = msg;
	this->sUrl = sUrl;
	this->pListCtrl = pListCtrl;
	this->sPath = sPath;
	this->lParam = lParam;
	this->wParam = wParam;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnFileReadtagsfrommp3file();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_COMMAND(ID_FILE_READTAGSFROMMP3FILE, &CAboutDlg::OnFileReadtagsfrommp3file)
END_MESSAGE_MAP()


// CGetCoverDlg dialog




CGetCoverDlg::CGetCoverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetCoverDlg::IDD, pParent)
	, m_AppPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetCoverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ARTIST, m_ctrl_Artist);
	DDX_Control(pDX, IDC_ALBUM, m_ctrl_Album);
	DDX_Control(pDX, IDC_SOURCE, m_ctrl_Source);
	DDX_Control(pDX, IDC_SAVEPATH, m_ctrl_SavePath);
	DDX_Control(pDX, IDL_COVERS, m_ctrl_CoversList);
	DDX_Control(pDX, IDC_INFOBOX, m_ctrl_InfoBox);
	DDX_Control(pDX, IDC_RELEASEINFOEDIT, m_ctrl_ReleaseInfo);
	DDX_Control(pDX, IDC_FILEMASK, m_ctrl_FileMask);
}

BEGIN_MESSAGE_MAP(CGetCoverDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDB_SEARCH, &CGetCoverDlg::OnBnClickedSearch)
	ON_MESSAGE(WM_USER_DOWNLOAD_COMPLETE, OnDownloadComplete)
	ON_MESSAGE(WM_USER_UPDATE_INFO_BOX  , OnUpdateInfoBox)
	ON_MESSAGE(WM_USER_THUMBDOWNLOADED , OnThumbDownloaded)
	ON_WM_SIZE()
	ON_WM_RBUTTONUP()
	ON_NOTIFY(NM_RCLICK, IDL_COVERS, &CGetCoverDlg::OnNMRclickCovers)
	ON_COMMAND(IDC_LM_DOWNLOADCOVER, &CGetCoverDlg::OnLmDownloadcover)
	ON_COMMAND(IDC_LM_RELEASE_INFO, &CGetCoverDlg::OnLmReleaseInfo)
	ON_BN_CLICKED(IDB_SAVEAS, &CGetCoverDlg::OnBnClickedSaveas)
	ON_BN_CLICKED(IDC_DOWNLOAD, &CGetCoverDlg::OnBnClickedDownload)
	ON_NOTIFY(LVN_ITEMCHANGED, IDL_COVERS, &CGetCoverDlg::OnLvnItemchangedCovers)
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(NM_DBLCLK, IDL_COVERS, &CGetCoverDlg::OnNMDblclkCovers)
	ON_CBN_SELCHANGE(IDC_SOURCE, &CGetCoverDlg::OnCbnSelchangeSource)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_CLEARTHUMBNAILCACHE, &CGetCoverDlg::OnFileClearthumbnailcache)
	ON_EN_CHANGE(IDC_FILEMASK, &CGetCoverDlg::OnEnChangeFilemask)
	ON_BN_CLICKED(IDCANCEL, &CGetCoverDlg::OnBnClickedCancel)
	ON_COMMAND(ID_FILE_READTAGSFROMMP3FILE, &CGetCoverDlg::OnFileReadtagsfrommp3file)
END_MESSAGE_MAP()


// CGetCoverDlg message handlers

BOOL CGetCoverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_Thumb = new CxImage();

	LPITEMIDLIST pidl; 
	TCHAR apppath[MAX_PATH];
	
	::GetCurrentDirectory(MAX_PATH, apppath);
	_tcscat(apppath, _TEXT("\\"));

	m_AppDir = apppath;

	SHGetSpecialFolderLocation(GetSafeHwnd(), CSIDL_APPDATA, &pidl);
	{
		if (pidl==NULL)
		{
			::GetCurrentDirectory(MAX_PATH, apppath);
			_tcscat(apppath, _TEXT("\\"));
		}
		else
		{
			SHGetPathFromIDList(pidl,apppath);
			_tcscat(apppath, _TEXT("\\"));
			_tcscat(apppath, _TEXT(APP_FOLDER));
		}
	}
/*
	g_event = _TEXT("get_cover_download_thread_sync_event_");
	srand(::GetTickCount());

	CString rant, tick, md51, md52;
	tick.Format(_TEXT("%lld"), GetTickCount());
	rant.Format(_TEXT("%d"), rand());

	md5(md51, tick, tick.GetLength());
	md5(md52, rant, rant.GetLength());

	g_event += (md51+md52);

	pEvent = new CEvent(FALSE, TRUE, g_event, NULL);
	
	g_download = 0;
	*/

	m_AppPath = apppath;
	_tcscat(apppath, _TEXT("\\"));
	CreateDirectories(apppath);
	_tcscat(apppath, _TEXT(THUMB_CACHE));
	_tcscat(apppath, _TEXT("\\"));
	CreateDirectories(apppath);

	SEARCHDATA sd;
	sd.Set(0, IDI_SRC_RYM, CString(_TEXT("RateYourMusic.com")) , CString(_TEXT("rateyourmusic")));
	schData.Add(sd);
	sd.Set(1, IDI_SRC_AMZ, CString(_TEXT("Amazon.com")) , CString(_TEXT("amazon")));
	schData.Add(sd);

	if(schData.GetCount() > 1)
	{
		sd.Set(2, IDI_SRC_ALL, CString(_TEXT("All sources")) , CString(_TEXT("getall")) );
		schData.Add(sd);
	}
/*
	TCHAR *sources[] = {
		_TEXT("RateYourMusic.com"),
		_TEXT("Amazon.com"),
		NULL
	};
	*/
	int nPos = 0;

	Rearrange();

	GetDlgItem(IDC_DOWNLOAD)->EnableWindow(FALSE);

	COMBOBOXEXITEM cbi;
	cbi.mask=CBEIF_IMAGE|CBEIF_TEXT|CBEIF_SELECTEDIMAGE;
	m_IList.Create(16,16,ILC_MASK|ILC_COLOR32,8,8);
	
	for(nPos = 0; nPos < schData.GetCount(); nPos ++)
	{
		m_IList.Add(AfxGetApp()->LoadIcon(schData.GetAt(nPos).nResource));
	}

	m_IList.Add(AfxGetApp()->LoadIcon(IDI_SRC_UNK));

	m_IState.Create(16,16,ILC_MASK|ILC_COLOR32,8,8);

	m_IState.Add(AfxGetApp()->LoadIcon(IDI_ST_DW));
	m_IState.Add(AfxGetApp()->LoadIcon(IDI_ST_ER));
	m_IState.Add(AfxGetApp()->LoadIcon(IDI_ST_EX));
	m_IState.Add(AfxGetApp()->LoadIcon(IDI_ST_OK));


	m_ctrl_Source.SetImageList(&m_IList);

	LPTSTR cmd = GetCommandLine();
	int argc;
	TCHAR** argv = CommandLineToArgv(cmd, &argc);

	if(argc>1) m_ctrl_Artist.SetWindowText(argv[1]);
	if(argc>2) m_ctrl_Album.SetWindowText(argv[2]);
	if(argc>3) m_ctrl_SavePath.SetWindowText(argv[3]);
	else
	{
		TCHAR cur[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, cur);
		_tcscat(cur, _TEXT("\\"));
//		_tcscat(cur, DEFAULT_COVERFILE);
		m_ctrl_SavePath.SetWindowText(cur);
	}
	if(argc>4) m_ctrl_FileMask.SetWindowText(argv[4]);
	else m_ctrl_FileMask.SetWindowText(_TEXT("folder"));

	m_ctrl_CoversList.SetImageList(&m_IList, LVSIL_NORMAL);
	m_ctrl_CoversList.SetImageList(&m_IList, LVSIL_SMALL);
	m_ctrl_CoversList.SetImageList(&m_IState, LVSIL_STATE);

	m_ctrl_CoversList.InsertColumn(SUBI_RELEASE, TEXT_RELEASE, LVCFMT_LEFT, COL_RELEASE, -1);
	m_ctrl_CoversList.InsertColumn(SUBI_ARTIST, TEXT_ARTIST, LVCFMT_LEFT, COL_ARTIST, -1);
	m_ctrl_CoversList.InsertColumn(SUBI_ALBUM, TEXT_ALBUM, LVCFMT_LEFT, COL_ALBUM, -1);
	m_ctrl_CoversList.InsertColumn(SUBI_X, TEXT_X, LVCFMT_LEFT, COL_X, -1);
	m_ctrl_CoversList.InsertColumn(SUBI_Y, TEXT_Y, LVCFMT_LEFT, COL_Y, -1);
	m_ctrl_CoversList.InsertColumn(SUBI_FILESIZE, TEXT_FILESIZE, LVCFMT_LEFT, COL_FILESIZE, -1);
	m_ctrl_CoversList.InsertColumn(SUBI_MESSAGE, TEXT_MESSAGE, LVCFMT_LEFT, COL_MESSAGE, -1);
	m_ctrl_CoversList.InsertColumn(SUBI_THUMB, TEXT_THUMB, LVCFMT_LEFT, COL_THUMB, -1);

	m_ctrl_CoversList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);

	for(nPos = 0; nPos < schData.GetCount(); nPos ++)
	{
		cbi.iItem=nPos;
		cbi.cchTextMax=schData[nPos].sName.GetLength();

		cbi.pszText = new TCHAR[cbi.cchTextMax + 1];
		_tcscpy(cbi.pszText, schData[nPos].sName);

		cbi.iImage=nPos;
		cbi.iSelectedImage=nPos;
		m_ctrl_Source.InsertItem(&cbi);

		delete cbi.pszText;
	}

	m_ctrl_Source.SetCurSel(0);

	unsigned int IDThread;
	g_bCloseApp = FALSE;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, JobPool, (void*)&m_jobs, 0, &IDThread);
	VERIFY(CloseHandle(hThread));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetCoverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetCoverDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if(m_Thumb->IsValid())
		{
			m_cover.left-=THUMB_BORDER;
			m_cover.top-=THUMB_BORDER;
			m_cover.right+=THUMB_BORDER;
			m_cover.bottom+=THUMB_BORDER;

			CPen pen;
			pen.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_INACTIVEBORDER));
			CPen *oldPen = (CPen*)dc.SelectObject(&pen);
			dc.Rectangle(m_cover);
			dc.SelectObject(oldPen);

			m_cover.left+=THUMB_BORDER;
			m_cover.top+=THUMB_BORDER;
			m_cover.right-=THUMB_BORDER;
			m_cover.bottom-=THUMB_BORDER;

			m_Thumb->Draw(dc.GetSafeHdc(), m_cover);
		}
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetCoverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CGetCoverDlg::OnBnClickedSearch()
{
	if(m_ctrl_Artist.GetWindowTextLength() > 0 || m_ctrl_Album.GetWindowTextLength() > 0)
	{
//			EnableControls(FALSE);

			TCHAR artist[500];
			TCHAR album [500];

			artist[0]=_TCHAR(0);
			album[0]=_TCHAR(0);

			m_ctrl_Artist.GetWindowText(artist, 500);
			m_ctrl_Album.GetWindowText(album, 500);

			CString csUrl;
			int len;

			TCHAR * artist_ue = url_encode(artist, (int)_tcslen(artist), &len);
			TCHAR * album_ue  = url_encode(album , (int)_tcslen(album) , &len);

			csUrl =  _TEXT("http://dmz.caravan.ru/covers/search.php?art=");
			csUrl += artist_ue;
			csUrl += _TEXT("&alb=");
			csUrl += album_ue;
			csUrl += _TEXT("&src=");

			csUrl += schData[m_ctrl_Source.GetCurSel()].sParam;

			free(artist_ue);
			free(album_ue);

			CJob job(GetSafeHwnd(), csUrl, &m_ctrl_CoversList, &m_ctrl_InfoBox, &rlsData, &schData, NULL);
			g_job_access.Lock();
			m_jobs.Add(job);
			g_job_access.Unlock();

//			InitStates();

	}
	else
	{
		MessageBox(_TEXT("Enter artist or album name"), _TEXT("Error"), MB_ICONERROR|MB_OK);
		return ;
	}

	// TODO: Add your control notification handler code here
}

LRESULT CGetCoverDlg::OnDownloadComplete(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
void CGetCoverDlg::OnNMRclickCovers(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if(m_ctrl_CoversList.GetSelectedCount() < 1)
	{
		*pResult = 1;
		return;
	}

	CMenu menu;
	if(!menu.LoadMenu(IDM_COVERBOX))
	{
		*pResult = 1;
		return;
	}

	CMenu* pSubMenu = menu.GetSubMenu(0);
	if (!pSubMenu)
	{
		*pResult = 1;
		return;
	}

	int nSelCnt = m_ctrl_CoversList.GetSelectedCount();
	CString mask;
	m_ctrl_FileMask.GetWindowText(mask);
	int bEnable = (nSelCnt == 1 || (nSelCnt >=1 && !is_mask(mask)))?MF_ENABLED:MF_DISABLED|MF_GRAYED;
	UINT nState = pSubMenu->EnableMenuItem(0, MF_BYPOSITION|bEnable);
	
	CPoint mouse;
	GetCursorPos(&mouse);
	::TrackPopupMenu(pSubMenu->m_hMenu, 0, mouse.x, mouse.y, 0,	GetSafeHwnd(), NULL);

	*pResult = 0;
}

LRESULT CGetCoverDlg::OnUpdateInfoBox(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void CGetCoverDlg::OnLmDownloadcover()
{
	if(m_ctrl_CoversList.GetSelectedCount() < 1) return;
	POSITION pos = m_ctrl_CoversList.GetFirstSelectedItemPosition();

	int nItem, nItem_o;
	TCHAR szSavePath[MAX_PATH];
	BOOL bPath;

	do {
		m_ctrl_SavePath.GetWindowText(szSavePath, MAX_PATH);
		if(_tcslen(szSavePath) == 0)
		{
			::GetCurrentDirectory(MAX_PATH, szSavePath);
			_tcscat(szSavePath, _TEXT("\\"));
			m_ctrl_SavePath.SetWindowText(szSavePath);
		}

		DWORD dwAttr=GetFileAttributes(szSavePath);
		if (dwAttr != (DWORD)(-1) && dwAttr & FILE_ATTRIBUTE_DIRECTORY) bPath = TRUE;
		else bPath = FALSE;

		if (bPath) break;

		OnBnClickedSaveas();
	} while(1);

	while(pos)
	{
		nItem_o = m_ctrl_CoversList.GetNextSelectedItem(pos);
		nItem = (int) m_ctrl_CoversList.GetItemData(nItem_o);

		m_ctrl_CoversList.SetItemText(nItem, SUBI_MESSAGE, _TEXT(""));
		m_ctrl_CoversList.SetItemState(nItem, 0, LVIS_STATEIMAGEMASK );

		CString savePath;
		m_ctrl_SavePath.GetWindowText(savePath);

		if(savePath.Right(1).Compare(_TEXT("\\")) != 0)
			savePath += _TEXT("\\");

		CString mask;
		m_ctrl_FileMask.GetWindowText(mask);
		savePath += mask;
		if(!is_mask(mask))
		{
			savePath += _TEXT("_");
			savePath += rlsData[nItem].md5;
			savePath += _TEXT(".jpg");
		}

		if(::GetFileAttributes(savePath) == (DWORD)(-1) || is_mask(mask))
		{
			CJob job(GetSafeHwnd(), rlsData[nItem].cover, &m_ctrl_CoversList, savePath, NULL, nItem_o);
			job.SetJob(JOB_COVER);
			m_ctrl_CoversList.SetItemState(nItem_o, STATE_DW, LVIS_STATEIMAGEMASK );
			g_job_access.Lock();
			m_jobs.Add(job);
			g_job_access.Unlock();
		}
		else
		{
			m_ctrl_CoversList.SetItemState(nItem_o, STATE_EX, LVIS_STATEIMAGEMASK );
			m_ctrl_CoversList.SetItemText(nItem_o, SUBI_MESSAGE, _TEXT("Cover already exists"));
		}
	}
}

void CGetCoverDlg::OnLmReleaseInfo()
{
	if(m_ctrl_CoversList.GetSelectedCount() < 1) return;
	POSITION pos = m_ctrl_CoversList.GetFirstSelectedItemPosition();

	int nItem;
	while(pos)
	{
		nItem = m_ctrl_CoversList.GetNextSelectedItem(pos);
	
		ShellExecute(GetSafeHwnd(), _TEXT("open"), 
			m_ctrl_CoversList.GetItemText(nItem, 0),
			NULL, NULL, SW_SHOWDEFAULT);
	}
}

void CGetCoverDlg::OnBnClickedSaveas()
{
	BROWSEINFO bi;
	TCHAR path[MAX_PATH];
	TCHAR startpath[MAX_PATH];
	LPITEMIDLIST pidl;

	m_ctrl_SavePath.GetWindowTextW(startpath, MAX_PATH);

	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = path;
	bi.lpszTitle = _TEXT("Specify a folder to save covers into");
	bi.ulFlags = BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_NEWDIALOGSTYLE;
	bi.lpfn = (BFFCALLBACK)BrowseCallbackProc;;
	bi.lParam = LPARAM(startpath);

	if(pidl = SHBrowseForFolder(&bi))
	{
		if(SHGetPathFromIDList(pidl, path))
		{
			m_ctrl_SavePath.SetWindowText(path);
		}
	}
}

void CGetCoverDlg::OnBnClickedDownload()
{
	OnLmDownloadcover();
}

void CGetCoverDlg::OnLvnItemchangedCovers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelCnt = m_ctrl_CoversList.GetSelectedCount();
	if(m_Thumb->IsValid()) m_Thumb->Destroy();

	if(nSelCnt == 1)
	{
		ShowReleaseInfo();
	}
	else
	{
		if(m_Thumb->IsValid()) m_Thumb->Destroy();
		m_ctrl_ReleaseInfo.SetWindowText(_TEXT(""));
	}

	OnEnChangeFilemask();

	Invalidate();
}


void CGetCoverDlg::OnSize(UINT nType, int cx, int cy)
{
	Rearrange();
}
void CGetCoverDlg::Rearrange(void)
{
	if(!IsWindow(GetSafeHwnd())) return;
	CRect rect, pos, wnd;
	GetClientRect(&rect);
	GetWindowRect(&wnd);

	pos=CRect(10,104, -77, -7);
	CRect wsp=CRect(10,0,0,0);
	MapDialogRect(pos);
	MapDialogRect(wsp);
	pos.bottom += rect.Height()-5;
	pos.top = pos.bottom - (164 - wsp.left);
	pos.right = pos.left + (164 - wsp.left);

	m_cover = pos;

	int wFrame = (wnd.right  - rect.right) / 2;
	int wHeader = wnd.bottom - rect.bottom - wFrame;

	if(GetDlgItem(IDC_STATIC_TOP)->GetSafeHwnd() != NULL)
	{
		pos=CRect(7,7, -7, 61);
		MapDialogRect(pos);
		pos.right += rect.Width();
		GetDlgItem(IDC_STATIC_TOP)->MoveWindow(pos);
	}


	if(GetDlgItem(IDC_TITLE_AR)->GetSafeHwnd() != NULL)
	{
		pos = CRect(17,22,35,34);
		MapDialogRect(pos);
		GetDlgItem(IDC_TITLE_AR)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_ARTIST)->GetSafeHwnd() != NULL)
	{
		pos = CRect(41, 20, -20, 34);
		MapDialogRect(pos);
		pos.right+=rect.Width()/2;
		GetDlgItem(IDC_ARTIST)->MoveWindow(pos);
	}

	if(GetDlgItem(IDB_SEARCH)->GetSafeHwnd() != NULL)
	{
		pos = CRect(41, 38, -20, 52);
		MapDialogRect(pos);
		pos.right+=rect.Width()/2;
		GetDlgItem(IDB_SEARCH)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_TITLE_AL)->GetSafeHwnd() != NULL)
	{
		pos = CRect(-7,22,20,34);
		MapDialogRect(pos);
		pos.left += rect.Width()/2;
		pos.right += rect.Width()/2;
		GetDlgItem(IDC_TITLE_AL)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_ALBUM)->GetSafeHwnd() != NULL)
	{
		pos = CRect(20, 20, -18, 34);
		MapDialogRect(pos);
		pos.left+=rect.Width()/2;
		pos.right+=rect.Width();
		GetDlgItem(IDC_ALBUM)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_TITLE_SR)->GetSafeHwnd() != NULL)
	{
		pos = CRect(-7,40,20,52);
		MapDialogRect(pos);
		pos.left += rect.Width()/2;
		pos.right += rect.Width()/2;
		GetDlgItem(IDC_TITLE_SR)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_SOURCE)->GetSafeHwnd() != NULL)
	{
		pos = CRect(20, 38, -18, 90);
		MapDialogRect(pos);
		pos.left+=rect.Width()/2;
		pos.right+=rect.Width();
		GetDlgItem(IDC_SOURCE)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_INFOBOX)->GetSafeHwnd() != NULL)
	{
		pos=CRect(7,62, -7, 81);
		MapDialogRect(pos);
		pos.right += rect.Width();
		GetDlgItem(IDC_INFOBOX)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_DWNBOX)->GetSafeHwnd() != NULL)
	{
		pos=CRect(7,81, -7, 100);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		GetDlgItem(IDC_DWNBOX)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_STATIC_BOT)->GetSafeHwnd() != NULL)
	{
		pos=CRect(7,101, -7, -27);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		pos.bottom += rect.Height() - 150;		
		GetDlgItem(IDC_STATIC_BOT)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_RELEASEINFO)->GetSafeHwnd() != NULL)
	{
		pos=CRect(7,101, -77, -7);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		pos.bottom += rect.Height();
		pos.top = pos.bottom - 170;
		GetDlgItem(IDC_RELEASEINFO)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_RELEASEINFOEDIT)->GetSafeHwnd() != NULL)
	{
		pos=CRect(10, 101, -80, -10);
		MapDialogRect(pos);
		CRect r(9,0,0,0);
		MapDialogRect(r);

		pos.left += (172 - r.left);
		pos.right += rect.Width();		
		pos.bottom += rect.Height();
		pos.top = pos.bottom - (170 - r.left);
		GetDlgItem(IDC_RELEASEINFOEDIT)->MoveWindow(pos);

//		GetDlgItem(IDC_RELEASEINFOEDIT)->Invalidate();
	}

	if(GetDlgItem(IDL_COVERS)->GetSafeHwnd() != NULL)
	{
		pos=CRect(14,130, -14, -34);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		pos.bottom += rect.Height() - 150;		
		GetDlgItem(IDL_COVERS)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_DOWNLOAD)->GetSafeHwnd() != NULL)
	{
		pos=CRect(-94, 111, -16, 125);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		pos.left += rect.Width();		
		GetDlgItem(IDC_DOWNLOAD)->MoveWindow(pos);
	}

	if(GetDlgItem(IDB_SAVEAS)->GetSafeHwnd() != NULL)
	{
		pos=CRect(-119, 111, -97, 125);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		pos.left += rect.Width();		
		GetDlgItem(IDB_SAVEAS)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_SAVEPATH)->GetSafeHwnd() != NULL)
	{
		pos=CRect(46, 111, -122, 124);
		MapDialogRect(pos);
		pos.right += rect.Width() - 80;		
		GetDlgItem(IDC_SAVEPATH)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_FILEMASK)->GetSafeHwnd() != NULL)
	{
		pos=CRect(46, 111, -122, 124);
		MapDialogRect(pos);
		pos.right += rect.Width();	
		pos.left += pos.right - 140;
		GetDlgItem(IDC_FILEMASK)->MoveWindow(pos);
	}

	if(GetDlgItem(IDC_ICONIMAGE)->GetSafeHwnd() != NULL)
	{
		pos=CRect(-43, -75, -22, -55);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		pos.bottom += rect.Height();		
		pos.left += rect.Width();		
		pos.top += rect.Height();		
		GetDlgItem(IDC_ICONIMAGE)->MoveWindow(pos);
		
	}

	if(GetDlgItem(IDCANCEL)->GetSafeHwnd() != NULL)
	{
		pos=CRect(-57, -23, -7, -7);
		MapDialogRect(pos);
		pos.right += rect.Width();		
		pos.bottom += rect.Height();		
		pos.left += rect.Width();		
		pos.top += rect.Height();		
		GetDlgItem(IDCANCEL)->MoveWindow(pos);
	}

	Invalidate();
}

void CGetCoverDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CRect r(0,0, 465, 360);
	MapDialogRect(r);
	lpMMI->ptMinTrackSize=CPoint(r.Width(), r.Height());
	//CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

CString CGetCoverDlg::FullPath(CString& fn)
{
		CString path;

		m_ctrl_SavePath.GetWindowText(path);

		if(path.Right(1).Compare(_TEXT("\\")) != 0)
			path += _TEXT("\\");

//		CString dir=path;

		CString mask;
		m_ctrl_FileMask.GetWindowText(mask);
		path += mask;
		if(!is_mask(mask))
		{
			path += _TEXT("_");
			path += fn;
			path += _TEXT(".jpg");
		}

		return path;
}

void CGetCoverDlg::InitStates()
{
	int nItem = m_ctrl_CoversList.GetItemCount();
	int nPos;
	for(int i =0; i<nItem;i++)
	{
		nPos = (int)m_ctrl_CoversList.GetItemData(i);

		CString path = FullPath(rlsData[nPos].md5);
		if(::GetFileAttributes(path) != (DWORD)(-1))
		{
			m_ctrl_CoversList.SetItemState(i, STATE_EX, LVIS_STATEIMAGEMASK);
		}
		else
		{
			if(m_ctrl_CoversList.GetItemState(i, LVIS_STATEIMAGEMASK) == STATE_EX)
				m_ctrl_CoversList.SetItemState(i, 0, LVIS_STATEIMAGEMASK);
		}
	}
}

void CGetCoverDlg::OnNMDblclkCovers(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(m_ctrl_CoversList.GetSelectedCount() == 1)
	{
		POSITION pos = m_ctrl_CoversList.GetFirstSelectedItemPosition();
		int nItem = m_ctrl_CoversList.GetNextSelectedItem(pos);
		nItem = (int) m_ctrl_CoversList.GetItemData(nItem);

		CString path = FullPath(rlsData[nItem].md5);

		if(::GetFileAttributes(path) != (DWORD)(-1))
		{
			ShellExecute(NULL, _TEXT("open"), 
				path,
				NULL, NULL, SW_SHOWDEFAULT);
		}
		else OnLmDownloadcover();
	}
	
	*pResult = 0;
}

void CGetCoverDlg::OnCbnSelchangeSource()
{
	// TODO: Add your control notification handler code here
}

void CGetCoverDlg::EnableControls(BOOL bF)
{
	return;
	int controls[] = {
		IDC_DOWNLOAD,
		IDC_SOURCE,
		IDB_SEARCH,
		IDL_COVERS,
		IDC_SAVEPATH,
		IDB_SAVEAS,
		IDC_ARTIST,
		IDC_ALBUM,
		NULL
	};

	int* ctrl = controls;

	while(*ctrl)
	{
		GetDlgItem(*ctrl)->EnableWindow(bF);
		Sleep(2000);
		ctrl++;
	}
}

static int WINAPI BrowseCallbackProc(HWND hWnd,UINT uMsg,LPARAM lParam, LPARAM lpData)
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		if(lpData) SendMessage(hWnd,BFFM_SETSELECTION,TRUE,(LONG)lpData);
		break;
	case BFFM_SELCHANGED: 
		{
			if(!IsBadReadPtr((PVOID)lParam,MAX_PATH))
			{
				TCHAR szDir[MAX_PATH];
				if (SHGetPathFromIDList((LPITEMIDLIST)lParam, szDir))
					SendMessage(hWnd,BFFM_SETSTATUSTEXT,0, reinterpret_cast<LONG>(szDir));
			}
		}
		break;
	}
	return 0;
}

void CGetCoverDlg::OnDestroy() 
{
	if(m_Thumb->IsValid()) m_Thumb->Destroy();
	delete m_Thumb;
	CDialog::OnDestroy();

//	delete pEvent;
	TRACE("Dlg done\n");
}

void CGetCoverDlg::OnFileClearthumbnailcache()
{
	if(MessageBox(_TEXT("Do you really want to delete ALL cached thumbnails?"), _TEXT("Attention!"), MB_YESNO|MB_ICONQUESTION ) == IDNO) return;
	CFileFind finder;
	CString path;
	path.Format(_TEXT("%s\\%s\\*"), m_AppPath, _TEXT(THUMB_CACHE));
	BOOL bResult = finder.FindFile(path);
	
	while(bResult)
	{
		bResult = finder.FindNextFile();
		path = finder.GetFilePath();
		if(!finder.IsDirectory())
		{
			::DeleteFile(path);
		}
	}

	MessageBox(_TEXT("Cache cleared"), _TEXT("Done"), MB_OK | MB_ICONINFORMATION);
}

void CGetCoverDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
}

BOOL CGetCoverDlg::is_mask(CString &mask)
{
	if(mask.Find(_TEXT(".jpg")) == mask.GetLength()-4 || mask.Find(_TEXT(".jpeg")) == mask.GetLength()-5) return TRUE;
	else return FALSE;
}
void CGetCoverDlg::OnEnChangeFilemask()
{
	int nSelCnt = m_ctrl_CoversList.GetSelectedCount();
	CString mask;
	m_ctrl_FileMask.GetWindowText(mask);
	GetDlgItem(IDC_DOWNLOAD)->EnableWindow(nSelCnt == 1 || (nSelCnt >=1 && !is_mask(mask)));
	InitStates();
}

void CGetCoverDlg::OnBnClickedCancel()
{
	g_bCloseApp = TRUE;
	TRACE("Waiting for the job thread to finish\n");
	::WaitForSingleObject(g_JobEvent.m_hObject, INFINITE);

	OnCancel();
}

LRESULT CGetCoverDlg::OnThumbDownloaded(WPARAM wParam, LPARAM lParam)
{
	ShowReleaseInfo(FALSE);
	Invalidate();
	return 0;
}

void CGetCoverDlg::ShowReleaseInfo(BOOL bUpload)
{
	POSITION pos = m_ctrl_CoversList.GetFirstSelectedItemPosition();
	int nItem_o = m_ctrl_CoversList.GetNextSelectedItem(pos);
	int nItem = (int) m_ctrl_CoversList.GetItemData(nItem_o);

	CString info;
	CString thumb;

	info.Format(_TEXT(
			"\
Release info: %s\r\n\r\n\
Cover url: %s\r\n\r\n\
Artist: %s\r\n\r\n\
Album: %s\r\n\r\n\
		"),
		rlsData[nItem].link,
		rlsData[nItem].cover,
		rlsData[nItem].artist,
		rlsData[nItem].album
	);

	m_ctrl_ReleaseInfo.SetWindowText(info);

	thumb = m_AppPath + _TEXT("\\") + _TEXT(THUMB_CACHE) + _TEXT("\\") + rlsData[nItem].md5_thumb + _TEXT(".jpg");
	CString md5;

	if(::GetFileAttributes(thumb) == (DWORD)(-1))
	{
		if(bUpload)
		{
			CString thumb_fs = thumb;
			thumb = m_AppDir + _TEXT(LD_COVER);
			CJob job(GetSafeHwnd(), rlsData[nItem].thumb, &m_ctrl_CoversList, thumb_fs, WM_USER_THUMBDOWNLOADED, nItem_o);
			job.SetJob(JOB_THUMB);
			m_ctrl_CoversList.SetItemText(nItem_o, SUBI_THUMB, _TEXT("Fetching thumbnail..."));
			g_job_access.Lock();
			m_jobs.Add(job);
			g_job_access.Unlock();
		}
		else
		{
			thumb = m_AppDir + _TEXT(NO_COVER);
			m_ctrl_CoversList.SetItemText(nItem_o, SUBI_THUMB, _TEXT("Cannot download thumbnail"));
		}
	}
	else
	{
		md5_file(thumb, md5);
		if(md5.CompareNoCase(_TEXT(AMAZON_NOT_AN_IMAGE)) == 0)
		{
			thumb = m_AppDir + _TEXT(NO_COVER);
			m_ctrl_CoversList.SetItemText(nItem_o, SUBI_THUMB, _TEXT("Image doesn't exist on the server"));
		}
		else
		{
			if(!bUpload)
				m_ctrl_CoversList.SetItemText(nItem_o, SUBI_THUMB, _TEXT("Downloaded"));
			else
				m_ctrl_CoversList.SetItemText(nItem_o, SUBI_THUMB, _TEXT("Found in cache"));
		}
	}

//	MessageBox(thumb);
	m_Thumb->Load(thumb);	
}
void CAboutDlg::OnFileReadtagsfrommp3file()
{
	// TODO: Add your command handler code here
}

void CGetCoverDlg::OnFileReadtagsfrommp3file()
{
	CFileDialog fdlg(TRUE, _TEXT("mp3"), NULL, OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_FORCESHOWHIDDEN|OFN_PATHMUSTEXIST, _TEXT("MP3 Files (*.mp3)|*.mp3||"), this);
	if(fdlg.DoModal())
	{
		CString filename = fdlg.GetPathName();
		TCHAR path_buffer[_MAX_PATH];
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];

		_tsplitpath(filename, drive, dir, fname, ext);

		std::string filename_ansi;
		tstring d;
		assign_ansi_from_os(filename_ansi, filename);

		MP3FileInfo info;
		info.Init(filename_ansi.c_str());

		CString sDir = CString(drive) + CString(dir);
		GetDlgItem(IDC_SAVEPATH)->SetWindowText(sDir);
		if(info.szArtist)
		{
			assign_os_from_ansi(d, info.szArtist);
			GetDlgItem(IDC_ARTIST)->SetWindowText(d.c_str());
		}
		else GetDlgItem(IDC_ARTIST)->SetWindowText(_TEXT(""));

		if(info.szAlbum)
		{
			assign_os_from_ansi(d, info.szAlbum);
			GetDlgItem(IDC_ALBUM)->SetWindowText(d.c_str());
		}
		else GetDlgItem(IDC_ALBUM)->SetWindowText(_TEXT(""));

	}

}
