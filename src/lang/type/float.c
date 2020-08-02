#include "_lang_.h"



int
main(void) {
  
  return 0;
}

void
test_float_type(void) {
  float f = 3.14f;
  double d = 2.7182; /* non suffix means double */
	long double ld = 2.718281828459L;

	printf("%20s=%02zu, %020f, 0x%016x\n",
				 "sizeof(float)", sizeof(f), f, *(unsigned int*)&f);
	
	printf("%20s=%02zu, %020lf, 0x%16lx\n",
				 "sizeof(double)", sizeof(d), d, *(unsigned long*)&d);
	
	printf("%20s=%02zu, %020Lf, 0x%16llx\n",
				 "sizeof(long double)", sizeof(ld), ld, *(unsigned long long*)&ld);
}
