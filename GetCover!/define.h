#include <string>

#define SUBI_RELEASE	0
#define SUBI_ARTIST		1
#define SUBI_ALBUM		2
#define SUBI_X			3
#define SUBI_Y			4
#define SUBI_FILESIZE	5
#define SUBI_MESSAGE	6
#define SUBI_THUMB		7

#define COL_RELEASE		50
#define COL_ARTIST		110
#define COL_ALBUM		110
#define COL_X			40
#define COL_Y			40
#define COL_FILESIZE	80
#define COL_MESSAGE		110
#define COL_THUMB		110

#define TEXT_RELEASE	_TEXT("Source")
#define TEXT_ARTIST		_TEXT("Artist")
#define TEXT_ALBUM		_TEXT("Album")
#define TEXT_X			_TEXT("Width")
#define TEXT_Y			_TEXT("Height")
#define TEXT_FILESIZE	_TEXT("Filesize")
#define TEXT_MESSAGE	_TEXT("Cover progress")
#define TEXT_THUMB		_TEXT("Thumb progress")

#define JOB_NONE	100
#define JOB_SEARCH	101
#define JOB_THUMB	102
#define JOB_COVER	103

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

typedef struct {
	CString src;
	CString uid;
	CString link;
	CString cover;
	CString thumb;
	CString artist;
	CString album;

	CString x;
	CString y;
	CString filesize;

	int nx;
	int ny;
	int nfilesize;

	CString filesize_fmt;

	DWORD_PTR dwId;
	int nIcon;

	CString md5;
	CString md5_thumb;

	void Set (tstring _src, tstring _uid, tstring _link, tstring _cover, tstring _thumb, tstring _artist, tstring _album, tstring _x, tstring _y, tstring _filesize)
	{
		src = _src.c_str();
		uid = _uid.c_str();
		link = _link.c_str();
		cover = _cover.c_str();
		thumb = _thumb.c_str();
		artist = _artist.c_str();
		album = _album.c_str();
		x = _x.c_str();
		y = _y.c_str();
		filesize = _filesize.c_str();

		nx = _ttoi(x);
		ny = _ttoi(y);
		nfilesize = _ttoi(filesize);

		double a = (double)nfilesize;
		CString pfx=_TEXT("B");

		if(a >=1000)
		{
			a/=1024;
			pfx = _TEXT("kB");
			if(a >=1024)
			{
				a/=1024;
				pfx = _TEXT("MB");
				if(a >=1024)
				{
					a/=1024;
					pfx = _TEXT("GB");
				}
			}
		}

		filesize_fmt.Format(_TEXT("%.1f %s"), a, pfx);
	}
} RELEASEDATA;

typedef struct {
	int nIcon;
	int nResource;
	CString sName;
	CString sParam;

	void Set(int _nIcon, int _nResource, CString _sName, CString _sParam)
	{
		nIcon = _nIcon;
		nResource = _nResource;
		sName = _sName;
		sParam = _sParam;
	}
} SEARCHDATA;

typedef CArray<RELEASEDATA> RLSARRAY;
typedef CArray<SEARCHDATA> SRCHARRAY;

class CJob {
public:
	int nJob;
	CString sUrl;
	CListCtrl* pListCtrl;
	HWND hWnd;
	UINT msg;

	LPARAM lParam;
	WPARAM wParam;
	
	//JOB_SEARCH
	RLSARRAY* pRls;
	SRCHARRAY* pSrch;
	CEdit* pInfo;
	

	//JOB_THUMB
	//JOB_COVER
	CString sPath;

	//JOB_THUMB

	//JOB_COVER
	int nItem;

	CJob(HWND hWnd, CString& sUrl, CListCtrl* pListCtrl, CString& sPath, UINT msg, int nItem, LPARAM lPAram = 0, WPARAM wParam = 0);
	CJob(HWND hWnd, CString& sUrl, CListCtrl* pListCtrl, CEdit* pInfo, RLSARRAY* pRls, SRCHARRAY* pSrch, UINT msg, LPARAM lParam = 0, WPARAM wParam = 0);
//	CJob(HWND hWnd, CString& sUrl, CListCtrl* pListCtrl, CString& sPath, UINT msg, int nItem, LPARAM lParam = 0, WPARAM wParam = 0);
	CJob();
	inline void SetJob(int nJob) {this->nJob = nJob;};
};

typedef CArray<CJob> CJobs;

#define AMAZON_NOT_AN_IMAGE "10E0C38F29FB91BED65E950B022E5054"

#define STATE_DW INDEXTOSTATEIMAGEMASK(1)
#define STATE_ER INDEXTOSTATEIMAGEMASK(2)
#define STATE_EX INDEXTOSTATEIMAGEMASK(3)
#define STATE_OK INDEXTOSTATEIMAGEMASK(4)
