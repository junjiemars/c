#include <_memory_.h>
#include <stdio.h>
#include <string.h>


typedef struct {
	int numerator;
	int denominator;
} fraction_s;


typedef struct {
	char *name;
	char suid[NM_PTR_LEN];
	int32_t units;
} student_s;


#define _VAL_ 0x11223344
#define _GAP_ 4

#if MSVC
#pragma warning(disable : 4996) /* _CRT_SECURE_NO_WARNINGS */
#endif


void
basic_layout() {
	int head[_GAP_] = { 0 };
	fraction_s f = { .numerator = 22, .denominator = 7 };
	int tail[_GAP_] = { 0 };

	_unused_(head);
	_unused_(tail);

	printf("\nBASIC LAYOUT\n");
	printf("----------\n");

  printf("&(struct) == &(struct->1st) \t\t=> %s (%p)\n", 
		_bool_(&f == (fraction_s*)&f.numerator), &f);

	// dangerous:

	((fraction_s*)&f.denominator)->numerator = f.numerator;
	assert(f.numerator == f.denominator);

	((fraction_s*)&f.denominator)->denominator = _VAL_;
	assert(_VAL_ == *((int*)&f.denominator+1));

	assert(f.denominator == ((fraction_s*)&f.denominator)[0].numerator);
}

void 
complex_layout() {
	student_s friends[4];
	int _tail_[_GAP_] = { 0 };

	_unused_(_tail_);

	friends[0].name = friends[2].suid + 3;

	// risky

#ifdef RISKY
	#ifdef MSVC
		#pragma warning(disable : 4789) /* will be overrun */ 
	#endif
	friends[5].units = 21;
#endif

	strcpy(friends[1].suid, "1122334");
	strcpy(friends->name, "Tiger Woods");
	
}

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	basic_layout();
	complex_layout();
}
