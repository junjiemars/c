#include <_memory_.h>
#include <stdio.h>
#include <string.h>


typedef struct {
	int numerator;
	int denominator;
} fraction_s;


typedef struct {
	char *name;
	char suid[8];
	int units;
} student_s;


#if MSVC
#pragma warning(disable : 4996) /* _CRT_SECURE_NO_WARNINGS */
#endif


void
basic_layout() {
	fraction_s f = { .numerator = 0x1100, .denominator = 0x22 };
	int gap[sizeof(fraction_s)/sizeof(int)];

	// risky:

	((fraction_s*)&f.denominator)->numerator = f.numerator;
	/* f.numerator == f.denominator) => true */

  gap[0] = 0x33;
	((fraction_s*)&f.denominator)->denominator = gap[0];
	/* gap[0] == *((int*)&f.denominator+1) => true */

  gap[0] = ((fraction_s*)&f.denominator)[0].numerator;
  /* gap[0] == f.denominator => true */
}

void 
complex_layout() {
	student_s friends[4];

	friends[0].name = friends[2].suid + 3;

	// risky:

#ifdef RISKY

  student_s gap;

  _unused_(gap);


	#ifdef MSVC
		#pragma warning(disable : 4789) /* will be overrun */ 
	#endif 

	friends[5].units = 21;

#endif /* end of RISKY */

	strcpy(friends[1].suid, "1122334");
	strcpy(friends->name, "Tiger Woods");

#ifdef CLANG
	memcpy((char*)&friends[0].units,
         (const char*)&friends[2].units, 
         strlen((const char*)&friends[2].units));
#else
	strcpy((char*)&friends[0].units,
         (const char*)&friends[2].units);	
#endif

	*(char***)&(((fraction_s*)&friends)[3].denominator)
    = &friends[0].name+1;
}

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("sizeof(struct fraction_s)=%zu\n", sizeof(fraction_s));
	printf("sizeof(struct student_s)=%zu\n", sizeof(student_s));

	basic_layout();
	complex_layout();
}
