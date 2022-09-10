#include <_mach_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
	int numerator;
	int denominator;
} fraction_s;


typedef struct
{
	char  *name;
	char   suid[8];
	int    units;
} student_s;


static void test_stack_layout(void);
static void test_heap_layout(void);
static void test_complex_layout(void);

int
main(void)
{
	printf("sizeof(struct fraction_s) = %4zu\n", sizeof(fraction_s));
	printf("sizeof(struct student_s)  = %4zu\n", sizeof(student_s));

	test_stack_layout();
  test_heap_layout();
	test_complex_layout();
}


void
test_stack_layout(void)
{
#if (_RISKY_)
  int  gap[sizeof(fraction_s)/sizeof(int)];
#endif

	fraction_s f      =
    {
      .numerator    =  0x1100,
      .denominator  =  0x22
    };

	((fraction_s*) &f.denominator)->numerator = f.numerator;
	assert(f.numerator == f.denominator);

#if (_RISKY_)
  gap[0]  =  0x33;

  /* (&f)[1]->numerator */
  assert(gap[0] == ((fraction_s*) ((char*) &f + sizeof(f)))->numerator);

	((fraction_s*) &gap[1])->numerator = gap[0];
  assert(gap[0] == (&f)[1].denominator);

#endif

}

void
test_complex_layout(void)
{
#if (_RISKY_)
  __attribute__((unused)) student_s  gap;
#endif

	student_s  ss[4];

  /* strcpy(ss[2].suid, "ABCD"); */
  memcpy(ss[2].suid, "ABCD", sizeof("ABCD"));
	ss[0].name = ss[2].suid + 3;

	strcpy(ss[1].suid, "aabbccd");
  assert(strcmp(ss[1].suid, "aabbccd") == 0);

#if (_RISKY_)

	strcpy(ss->name, "Tiger Woods");
  assert(strcmp(ss->name, ss[2].suid + 3) == 0);
  assert(strcmp((char*) &ss[3].name, "ds") == 0);

  ss[2].units = 0x11223344;
  strcpy((char*) &ss[0].units, (const char*) &ss[2].units);

#endif  /* end of _RISKY_ */

}

void
test_heap_layout(void)
{
  fraction_s  *f  =  malloc(sizeof(fraction_s));
  if (!f)
    {
      perror(NULL);
      return;
    }
  f->numerator = 0x1100;
  f->denominator = 0x22;

	assert(f->denominator == ((fraction_s*) &f->denominator)->numerator);

  free(f);
}
