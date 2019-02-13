#pragma once
#include "2013Internal.h"

#ifdef __cplusplus
extern "C" {
#endif

	int __cdecl VS2013_sprintf_s(
		char *string,
		size_t sizeInBytes,
		const char *format,
		...
	);

#ifdef __cplusplus
} // end extern "C"
#endif