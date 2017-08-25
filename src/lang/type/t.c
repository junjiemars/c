#include <_lang_.h>
#include <stdio.h>


#if CC_GCC == 1
	/* (unsigned init*)&f: */
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"  
#endif


int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

  float f0 = 3.14f;
  double f1 = 2.7182;
  printf("pi %f stored as %8x\n", f0, *(unsigned int*)&f0);
  printf("e %f stored as %8x\n", f1, *(unsigned int*)&f1);
}
