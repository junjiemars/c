#include "math1.h"
#include "geo.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int 
main() {
	double a = area_of_rect(4., 5.);
	printf("area of rect(%f, %f) = %f\n", 4., 5., a);

	// trunc toward to zero	
	printf("trunc(%f) = %f\n", 1.5, trunc(1.5));
	printf("trunc(%f) = %f\n", -1.5, trunc(-1.5));

	// floor toward to -infinite
	printf("floor(%f) = %f\n", 1.5, floor(1.5));
	printf("floor(%f) = %f\n", -1.5, floor(-1.5));

	// ceil toward to +infinite
	printf("ceil(%f) = %f\n", 1.5, ceil(1.5));
	printf("ceil(%f) = %f\n", -1.5, ceil(-1.5));

	/*
		round: return the integral value nearest to x rounding 
					 half-way cases away from zero, regardless of the 
					 current rounding direction.
	*/
	printf("round(%f) = %f\n", 1.4, round(1.4));
	printf("round(%f) = %f\n", -1.4, round(-1.4));
	printf("round(%f) = %f\n", 1.5, round(1.5));
	printf("round(%f) = %f\n", -1.5, round(-1.5));
	printf("round(%f) = %f\n", 2.5, round(2.5));
	printf("round(%f) = %f\n", -2.5, round(-2.5));

	return 0;
}
