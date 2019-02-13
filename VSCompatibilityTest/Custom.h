#pragma once


struct jose_iobuf {
	char *_ptr;
	int   _cnt;
	char *_base;
	int   _flag;
	int   _file;
	int   _charbuf;
	int   _bufsiz;
	char *_tmpfname;
};
typedef struct jose_iobuf JOSE_FILE;


/* locale dependent */
#define _LOCALE_ARG \
    _LocInfo

#define _LOCALE_ARG_DECL \
    _locale_t _LOCALE_ARG

#define _LOCALE_UPDATE \
    _LocaleUpdate _LocUpdate(_LOCALE_ARG)

#define _ISMBBLEAD(_Character) \
    _ismbblead_l((_Character), _LocUpdate.GetLocaleT())

#define _MBSDEC(_String, _Current) \
    _mbsdec((_String), (_Current))

#define _ISMBBLEADPREFIX(_Result, _StringStart, _BytePtr)               \
    {                                                                   \
        unsigned char *_Tmp_VAR, *_StringStart_VAR, *_BytePtr_VAR;      \
                                                                        \
        _StringStart_VAR = (_StringStart);                              \
        _BytePtr_VAR = (_BytePtr);                                      \
        _Tmp_VAR = _BytePtr_VAR;                                        \
        while ((_Tmp_VAR >= _StringStart_VAR) && _ISMBBLEAD(*_Tmp_VAR)) \
        {                                                               \
            _Tmp_VAR--;                                                 \
        }                                                               \
        (_Result) = ((_BytePtr_VAR - _Tmp_VAR) & 1) != 0;               \
    }

#define _LOCALE_SHORTCUT_TEST \
    _LocUpdate.GetLocaleT()->mbcinfo->ismbcodepage == 0

#define _USE_LOCALE_ARG 1




struct _tiddata {
	unsigned long   _tid;       /* thread ID */


	uintptr_t _thandle;         /* thread handle */

	int     _terrno;            /* errno value */
	unsigned long   _tdoserrno; /* _doserrno value */
	unsigned int    _fpds;      /* Floating Point data segment */
	unsigned long   _holdrand;  /* rand() seed value */
	char *      _token;         /* ptr to strtok() token */
	wchar_t *   _wtoken;        /* ptr to wcstok() token */
	unsigned char * _mtoken;    /* ptr to _mbstok() token */

	/* following pointers get malloc'd at runtime */
	char *      _errmsg;        /* ptr to strerror()/_strerror() buff */
	wchar_t *   _werrmsg;       /* ptr to _wcserror()/__wcserror() buff */
	char *      _namebuf0;      /* ptr to tmpnam() buffer */
	wchar_t *   _wnamebuf0;     /* ptr to _wtmpnam() buffer */
	char *      _namebuf1;      /* ptr to tmpfile() buffer */
	wchar_t *   _wnamebuf1;     /* ptr to _wtmpfile() buffer */
	char *      _asctimebuf;    /* ptr to asctime() buffer */
	wchar_t *   _wasctimebuf;   /* ptr to _wasctime() buffer */
	void *      _gmtimebuf;     /* ptr to gmtime() structure */
	char *      _cvtbuf;        /* ptr to ecvt()/fcvt buffer */
	unsigned char _con_ch_buf[MB_LEN_MAX];
	/* ptr to putch() buffer */
	unsigned short _ch_buf_used;   /* if the _con_ch_buf is used */

	/* following fields are needed by _beginthread code */
	void *      _initaddr;      /* initial user thread address */
	void *      _initarg;       /* initial user thread argument */

	/* following three fields are needed to support signal handling and
	 * runtime errors */
	void *      _pxcptacttab;   /* ptr to exception-action table */
	void *      _tpxcptinfoptrs; /* ptr to exception info pointers */
	int         _tfpecode;      /* float point exception code */

	/* pointer to the copy of the multibyte character information used by
	 * the thread */
	//pthreadmbcinfo  ptmbcinfo;

	/* pointer to the copy of the locale informaton used by the thead */
	//pthreadlocinfo  ptlocinfo;
	int         _ownlocale;     /* if 1, this thread owns its own locale */

	/* following field is needed by NLG routines */
	unsigned long   _NLG_dwCode;

	/*
	 * Per-Thread data needed by C++ Exception Handling
	 */
	void *      _terminate;     /* terminate() routine */
	void *      _unexpected;    /* unexpected() routine */
	void *      _translator;    /* S.E. translator */
	void *      _purecall;      /* called when pure virtual happens */
	void *      _curexception;  /* current exception */
	void *      _curcontext;    /* current exception context */
	int         _ProcessingThrow; /* for uncaught_exception */
	void *              _curexcspec;    /* for handling exceptions thrown from std::unexpected */
#if defined (_M_IA64) || defined (_M_AMD64)
	void *      _pExitContext;
	void *      _pUnwindContext;
	void *      _pFrameInfoChain;
	unsigned __int64    _ImageBase;
#if defined (_M_IA64)
	unsigned __int64    _TargetGp;
#endif  /* defined (_M_IA64) */
	unsigned __int64    _ThrowImageBase;
	void *      _pForeignException;
#elif defined (_M_IX86)
	void *      _pFrameInfoChain;
#endif  /* defined (_M_IX86) */
	//_setloc_struct _setloc_data;

	void *      _encode_ptr;    /* EncodePointer() routine */
	void *      _decode_ptr;    /* DecodePointer() routine */

	void *      _reserved1;     /* nothing */
	void *      _reserved2;     /* nothing */
	void *      _reserved3;     /* nothing */

	int _cxxReThrow;        /* Set to True if it's a rethrown C++ Exception */

	unsigned long __initDomain;     /* initial domain used by _beginthread[ex] for managed function */
};

typedef struct _tiddata * _ptiddata;



