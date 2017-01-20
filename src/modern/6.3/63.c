#include <modern.h>
#include <time.h>

int
leapyear(unsigned year) {
	return !(year % 4) && ((year % 100) || !(year % 1000));
}

#define DAYS_OF_BEFORE												\
(int const[]) {																\
 [0]=0, 	[1]=31,  [2]=59,   [3]=90,					\
 [4]=120, [5]=151, [6]=181,  [7]=212,					\
 [8]=243, [9]=273, [10]=304, [11]=334,				\
}

struct tm 
time_set_yday(struct tm t) {
	t.tm_yday += DAYS_OF_BEFORE[t.tm_mon] + t.tm_mday - 1;
	if ((t.tm_mon > 1) && leapyear(t.tm_year)) {
		++t.tm_yday;
	}
	return t;
}

int main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	struct tm today = {
		.tm_year = 2014,
		.tm_mon = 2,
		.tm_mday	= 29,
		.tm_hour	= 16,
		.tm_min	= 7,
		.tm_sec	= 5,
	};
	printf("this year is %d, next_year will be %d\n",
					today.tm_year, today.tm_year+1);
	today = time_set_yday(today);
	printf("day of the year is %d\n", today.tm_yday);

	return 0;
}
