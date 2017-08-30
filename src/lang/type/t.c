#include <_lang_.h>
#include <stdio.h>


#if GCC
	/* (unsigned init*)&f: */
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"  
#endif

void 
integer_type() {
  int i0 = 10;
  long i1 = 123L;
  printf("ten %i stored as 0x%08x\n", i0, *(unsigned int*)&i0);
  printf("hundred %li stored as 0x%08x\n", i1, *(unsigned int*)&i1);
}

void 
float_type() {
  float f0 = 3.14f;
  double f1 = 2.7182L;
  printf("pi %f stored as 0x%8x\n", f0, *(unsigned int*)&f0);
  printf("e %lf stored as 0x%8x\n", f1, *(unsigned int*)&f1);
}


int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

  integer_type();
  float_type();
}
