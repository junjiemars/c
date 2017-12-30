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


void
basic_layout() {
	fraction_s f = { .numerator = 0x1100, .denominator = 0x22 };
  
	((fraction_s*)&f.denominator)->numerator = f.numerator;
	/* f.numerator == f.denominator) => true */

#ifdef RISKY
	int gap[sizeof(fraction_s)/sizeof(int)];


  gap[0] = 0x33;
	((fraction_s*)&gap[1])->denominator = gap[0];
	/* gap[0] == f.numerator => true */

  gap[0] = ((fraction_s*)&f.denominator)[0].numerator;
  /* gap[0] == f.denominator => true */

#endif
}

void
complex_layout() {
	student_s friends[4];

	friends[0].name = friends[2].suid + 3;

	strcpy(friends[1].suid, "aabbccdd");
	strcpy(friends->name, "Tiger Woods");

  friends[2].units = 0x11223344;

#ifdef CLANG
	memcpy((char*)&friends[0].units,
         (const char*)&friends[2].units,
         strlen((const char*)&friends[2].units));
#else
	strcpy((char*)&friends[0].units,
         (const char*)&friends[2].units);
#endif

#ifdef RISKY

  student_s gap;
  _unused_(gap);

	friends[4].units = 21;

	*(char***)&(((fraction_s*)&friends)[3].denominator)
    = &friends[0].name+1;

#endif /* end of RISKY */
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
