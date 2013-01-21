// GetCover!Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxcoll.h"
/*
typedef struct {
	CString object;
	CByteArray data;
	DWORD	dwDataSize;
	CString host;
	INTERNET_PORT port;
	LPARAM lParam;
	WPARAM wParam;

	CString savePath;
	
	CListCtrl * list;

	HWND hWnd;

	TCHAR lastError[1024];
	DWORD dwLastError;
} THREADDATA;*/

// CGetCoverDlg dialog
class CGetCoverDlg : public CDialog
{
// Construction
public:
	CGetCoverDlg(CWnd* pParent = NULL);	// standard constructor
	void DECLARE_DINAMIC(CGetCoverDlg);

// Dialog Data
	enum { IDD = IDD_GETCOVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedSearch();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnDownloadComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateInfoBox(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	CEdit m_ctrl_Artist;
	CEdit m_ctrl_Album;
	CComboBoxEx m_ctrl_Source;
	CEdit m_ctrl_SavePath;
	CListCtrl m_ctrl_CoversList;
	CImageList m_IList, m_IState;
//	THREADDATA thData;
	CEdit m_ctrl_InfoBox;
	afx_msg void OnNMRclickCovers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void EnableControls(BOOL);

private:
//	CStringArray csaCovers;
	afx_msg void OnLmDownloadcover();
	afx_msg void OnLmReleaseInfo();
	afx_msg LRESULT OnThumbDownloaded(WPARAM , LPARAM );
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSaveas();
	afx_msg void OnBnClickedDownload();
	afx_msg void OnLvnItemchangedCovers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
private:
	void Rearrange(void);
	afx_msg void OnNMDblclkCovers(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeSource();
	afx_msg void OnDestroy();

	void ShowReleaseInfo(BOOL bUpload = TRUE);

	SRCHARRAY schData;
	RLSARRAY rlsData;
	static BOOL is_mask(CString &mask);
private:
	CString m_AppPath, m_AppDir;

	afx_msg void OnFileClearthumbnailcache();
	CEdit m_ctrl_ReleaseInfo;

	CRect m_cover;

	CxImage *m_Thumb;

	CEdit m_ctrl_FileMask;
	afx_msg void OnEnChangeFilemask();

	CString FullPath(CString& fn);
	void InitStates();

	CJobs m_jobs;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnFileReadtagsfrommp3file();
};
