extern unsigned _stdcall JobPool(void * parameter);
extern CCriticalSection g_job_access;
extern BOOL g_bCloseApp;
extern CEvent g_JobEvent;

#define BUFFER_SIZE 2048

void md5(CString& buf, const TCHAR* data, int len);
void md5_file(CString& file, CString &buf);

