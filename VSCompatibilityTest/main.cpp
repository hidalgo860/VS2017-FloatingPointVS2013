#include <stdio.h>
#include <cfloat>
#include <cmath>
#include <string>
#include <stdlib.h>
#include "2013VS_sprintf_s.h"

int main() {
	double x = 0.182696884245135;
	printf("FLT_RADIX = %d\n", FLT_RADIX);
	printf("DBL_DIG = %d\n", DBL_DIG);
	printf("DBL_MANT_DIG = %d\n", DBL_MANT_DIG);


	// VS2017 
	char buf[256];
	sprintf_s(buf, "%.*f", 14, x);
	printf("Value = %s\n", std::string(buf).c_str());

	// VS2013 backwards compatibility
	char buf2[256];
	VS2013_sprintf_s(buf2, sizeof(buf2), "%.*f", 14, x);
	printf("Value = %s\n", std::string(buf2).c_str());

	//OutputDebugString(buf);
	//printf("%.0f\n", pow(2.0, 80));
	//printf("%.17g\n%.17g\n%.17g\n", nextafter(x, 0.0), x, nextafter(x, 1.0));


	printf("c++ :", __cplusplus);

	system("PAUSE");
}