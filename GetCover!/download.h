static TCHAR hexchars[] = _T("0123456789ABCDEF");

TCHAR *url_encode(TCHAR const *s, int len, int *new_length)
{
	register TCHAR c;
	TCHAR *to, *start;
	TCHAR const *from, *end;
	
	from = (TCHAR*)s;
	end = from + len;
	start = to = (TCHAR *) malloc(sizeof(TCHAR) * (3*len + 1));
#ifdef TRACE
	TRACE("Malloced: %08x\n", start);
#endif

	while (from < end) {
		c = *from++;

		if (c == _TCHAR(' ')) {
			*to++ = _TCHAR('+');
		} else if ((c < _TCHAR('0') && c != _TCHAR('-') && c != _TCHAR('.')) ||
				   (c < _TCHAR('A') && c >  _TCHAR('9')) ||
				   (c > _TCHAR('Z') && c <  _TCHAR('a') && c != _TCHAR('_')) ||
				   (c > _TCHAR('z'))) {
			to[0] = _TCHAR('%');
			to[1] = _TCHAR(hexchars[c >> 4]);
			to[2] = _TCHAR(hexchars[c & 15]);
			to += 3;
		} else {
			*to++ = c;
		}
	}
	*to = _TCHAR(0);
	if (new_length) {
		*new_length = (int)(to - start);
	}
	return (TCHAR *) start;
}


static unsigned _stdcall DownloadThreadProc(void * parameter);


BOOL CreateDirectories(const TCHAR* dirpath)
{
	CString dir;
	dir.Format(_TEXT("%s"), dirpath);
	int fslash, bslash;
	int start=0;
	BOOL bError=TRUE;
	CString path;

	do
	{
		fslash=dir.Find(_TCHAR('/'),start);
		bslash=dir.Find(_TCHAR('\\'),start);

		if(fslash==-1) fslash=dir.GetLength()+1;
		if(bslash==-1) bslash=dir.GetLength()+1;
		if(fslash==bslash) break;

		start=(fslash<bslash)?fslash:bslash;
		path=dir.Left(start);
		start++;
		if(path.IsEmpty()) continue;
		int nLen=path.GetLength();
		if(nLen>=2) if(path.GetAt(nLen-1)==':') continue;
		if(nLen>=3) if(path.GetAt(nLen-2)==':') continue;

		if(!(bError=CreateDirectory(path.GetBuffer(path.GetLength()),NULL)))
			if(GetLastError()==ERROR_ALREADY_EXISTS)
				bError=TRUE;
	}while(bError);

	return bError;

}

    PTCHAR*
    CommandLineToArgv(
        PTCHAR CmdLine,
        int* _argc
        )
    {
        PTCHAR* argv;
        PTCHAR  _argv;
        ULONG   len;
        ULONG   argc;
        TCHAR   a;
        ULONG   i, j;

        BOOLEAN  in_QM;
        BOOLEAN  in_TEXT;
        BOOLEAN  in_SPACE;

        len = (int)_tcslen(CmdLine);
        i = ((len+2)/2)*sizeof(PVOID) + sizeof(PVOID);

        argv = (PTCHAR*)GlobalAlloc(GMEM_FIXED,
            i + (len+2)*sizeof(TCHAR));

        _argv = (PTCHAR)(((PUCHAR)argv)+i);

        argc = 0;
        argv[argc] = _argv;
        in_QM = FALSE;
        in_TEXT = FALSE;
        in_SPACE = TRUE;
        i = 0;
        j = 0;

        while( a = CmdLine[i] ) {
            if(in_QM) {
                if(a == '\"') {
                    in_QM = FALSE;
                } else {
                    _argv[j] = a;
                    j++;
                }
            } else {
                switch(a) {
                case '\"':
                    in_QM = TRUE;
                    in_TEXT = TRUE;
                    if(in_SPACE) {
                        argv[argc] = _argv+j;
                        argc++;
                    }
                    in_SPACE = FALSE;
                    break;
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                    if(in_TEXT) {
                        _argv[j] = '\0';
                        j++;
                    }
                    in_TEXT = FALSE;
                    in_SPACE = TRUE;
                    break;
                default:
                    in_TEXT = TRUE;
                    if(in_SPACE) {
                        argv[argc] = _argv+j;
                        argc++;
                    }
                    _argv[j] = a;
                    j++;
                    in_SPACE = FALSE;
                    break;
                }
            }
            i++;
        }
        _argv[j] = '\0';
        argv[argc] = NULL;

        (*_argc) = argc;
        return argv;
    }
