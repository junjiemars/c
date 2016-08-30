#include <cl_auto_config.h>
#include <cl_auto_headers.h>

#if (CL_HAVE_STDIO_H)
#include <stdio.h>
#endif


int main(int argc, const char *argv[]) {
	if (argc > 1) {
		printf("Hi, %s\n", argv[1]);
	}


#if (CL_HAVE_LOCALTIME_R)
#include <time.h>
	struct tm t; 
	time_t c=0; 
	localtime_r(&c, &t);
	printf("%d/%d/%d\n", t.tm_year, t.tm_mon, t.tm_mday);		
#endif

	return 0;
}
