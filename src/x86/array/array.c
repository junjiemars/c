#include "_x86_.h"
#include <stdio.h>

static void  offset(void);
static void  array(void);
static void  structure(void);

int
main(int argc, const char *argv[])
{
	(void) (argc);
	(void) (argv);

	offset();
	array();

	printf("sizeof(struct binky)=%zu\n", sizeof(struct binky));
	structure();
}

void
offset(void)
{
	int  i;
	int  a[20];

	i = 19;
	a[i] = 0x11223344;
	i[a]++;

  (void) i;
  (void) a;
}

void
array(void)
{
	int  a[20];

	a[19] = 0x11223344;

  (void) a;
}

void
structure(void)
{
	int           i;
	struct binky  a[4];

	i = 3;
	a[i].f = i;

  (void) i;
  (void) a;
}
