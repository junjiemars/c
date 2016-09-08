#include <math.h>

#include <geo.h>
#include <stdio.h>


double ref;

//double set_na(){
//	if (!ref) {
//		ref = 0./0.;
//		char *cr = (char *)(&ref);
//		cr[2]='a';
//	}
//	return ref;
//}

int is_na(double in){
	if (!ref) return 0;  //set_na was never called==>no NAs yet.

	char *cc = (char *)(&in);
	char *cr = (char *)(&ref);

	for (size_t i = 0; i < sizeof(double); i++)
		if (cc[i] != cr[i]) return 0;

	return 1;
}

int main(){

	double x = 1.0;//set_na();

	printf("8 is not a number = %i\n", is_na(8));
	//printf("0/0. is not a number = %i\n", isnan(0/0.));

	unsigned long lu = *(unsigned long*)&x;

	printf("nan spec: 0x%lx\n", lu);
	printf("0x%lx is not a number = %i, via self:is_na\n", 
		lu, is_na(x));

	printf("0x%lx is not a number = %i, via stdc:isnan\n", 
		lu, isnan(x));

	double a = area_of_rect(4., 5.);
	printf("area of rect(%f, %f) = %f\n", 4., 5., a);


	return 0;
}
