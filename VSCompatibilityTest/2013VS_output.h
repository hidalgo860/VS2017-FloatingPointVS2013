#pragma once
#include <stdio.h>
#include <tchar.h>
#include "2013Internal.h"
#include "2013setlocal.h"

/*
* floating point helper routines
*
* In the non-CRTDLL builds, these prototypes are immediately replaced by
* macros which replace them with calls through elements of the _cfltcvt_tab
* array, so we only pull them into a static-link build if floating point
* code is needed.
*/

errno_t __cdecl _cfltcvt(double *arg, char *buffer, size_t sizeInBytes,
	int format, int precision,
	int caps);
errno_t __cdecl _cfltcvt_l(double *arg, char *buffer, size_t sizeInBytes,
	int format, int precision,
	int caps, _locale_t plocinfo);

void __cdecl _cropzeros_l(char *_Buf, _locale_t _Locale);
void __cdecl _forcdecpt_l(char *_Buf, _locale_t _Locale);

#ifdef __cplusplus
extern "C" {
#endif



	int __cdecl _output_s_l(
		JOSE_FILE *stream,
		const _TCHAR *format,
		_locale_t plocinfo,
		va_list argptr
	);

#ifdef __cplusplus
} // end extern "C"
#endif
