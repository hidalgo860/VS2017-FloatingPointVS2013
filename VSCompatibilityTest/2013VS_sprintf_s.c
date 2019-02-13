/***
*sprintf.c - print formatted to string
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines sprintf() and _snprintf() - print formatted data to string
*
*******************************************************************************/

#include "2013VS_sprintf_s.h"
#include "2013VS_output.h"
#include "2013Internal.h"
#include "Custom.h"

#define MAXSTR INT_MAX

// #include <errno.h> should handle this , not sure whats going on
#define EINVAL          22
#define ERANGE          34
#define EILSEQ          42
#define STRUNCATE       80

#define _IOWRT    000020
#define _IOSTRG   000400


int __cdecl _vsnprintf_helper(
	OUTPUTFN outfn,
	char *string,
	size_t count,
	const char *format,
	_locale_t plocinfo,
	va_list ap
)
{
	FILE str = { 0 };
	JOSE_FILE *outfile = &str;
	int retval;

	_VALIDATE_RETURN((format != NULL), EINVAL, -1);

#ifdef _COUNT_
	_VALIDATE_RETURN((count == 0) || (string != NULL), EINVAL, -1);
#else  /* _COUNT_ */
	_VALIDATE_RETURN((string != NULL), EINVAL, -1);
#endif  /* _COUNT_ */

#ifndef _COUNT_
	outfile->_cnt = MAXSTR;
#else  /* _COUNT_ */
	if (count > INT_MAX)
	{
		/* old-style functions allow any large value to mean unbounded */
		outfile->_cnt = INT_MAX;
	}
	else
	{
		outfile->_cnt = (int)count;
	}
#endif  /* _COUNT_ */

	outfile->_flag = _IOWRT | _IOSTRG;
	outfile->_ptr = outfile->_base = string;

//TODO
#ifdef _SWPRINTFS_ERROR_RETURN_FIX
	retval = _output_l(outfile, format, plocinfo, ap);
#else  /* _SWPRINTFS_ERROR_RETURN_FIX */
	retval = outfn(outfile, format, plocinfo, ap);
#endif  /* _SWPRINTFS_ERROR_RETURN_FIX */

	if (string == NULL)
		return(retval);

#ifndef _SWPRINTFS_ERROR_RETURN_FIX

	_putc_nolock('\0', outfile);

	return(retval);
#else  /* _SWPRINTFS_ERROR_RETURN_FIX */
	if ((retval >= 0) && (_putc_nolock('\0', outfile) != EOF))
		return(retval);

	string[count - 1] = 0;

	if (outfile->_cnt < 0)
	{
		/* the buffer was too small; we return -2 to indicate truncation */
		return -2;
	}
	return -1;
#endif  /* _SWPRINTFS_ERROR_RETURN_FIX */
}

int __cdecl VS2013_vsprintf_s_l(
	char *string,
	size_t sizeInBytes,
	const char *format,
	_locale_t plocinfo,
	va_list ap
)
{
	int retvalue = -1;

	/* validation section */
	_VALIDATE_RETURN(format != NULL, EINVAL, -1);
	_VALIDATE_RETURN(string != NULL && sizeInBytes > 0, EINVAL, -1);

	retvalue = _vsnprintf_helper(_output_s_l, string, sizeInBytes, format, plocinfo, ap);
	if (retvalue < 0)
	{
		string[0] = 0;
		_SECURECRT__FILL_STRING(string, sizeInBytes, 1);
	}
	if (retvalue == -2)
	{
		_VALIDATE_RETURN(("Buffer too small", 0), ERANGE, -1);
	}
	if (retvalue >= 0)
	{
		_SECURECRT__FILL_STRING(string, sizeInBytes, retvalue + 1);
	}

	return retvalue;
}

int __cdecl VS2013_sprintf_s(
	char *string,
	size_t sizeInBytes,
	const char *format,
	...
)
{
	va_list arglist;
	va_start(arglist, format);
	return VS2013_vsprintf_s_l(string, sizeInBytes, format, NULL, arglist);
}