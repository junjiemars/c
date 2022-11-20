#include "_lang_.h"


#if (MSVC)
#  pragma warning(disable: 4456)
#elif (GCC)
#  pragma GCC diagnostic ignored "-Wunused-variable"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#elif (CLANG)
#  pragma clang diagnostic ignored "-Wunused-variable"
#  pragma clang diagnostic ignored "-Wunused-parameter"
/* #  pragma clang diagnostic ignored "-Wunused-but-set-variable" */
#endif


static void automatic_storage_class(void);
static void static_storage_class(void);
static void array_decay(char *restrict);
static void register_storage_class(register int x);
static void external_storage_class(void);


static int  f_int;

int
main(void)
{
	printf("\nautomatic storage class\n");
	printf("-------------------------\n");
	automatic_storage_class();
	automatic_storage_class();

	printf("\nregister storage class\n");
	printf("-----------------------\n");
	register_storage_class(0x11223344);

	printf("\nstatic storage class\n");
	printf("---------------------\n");
	static_storage_class();
	static_storage_class();
	static_storage_class();

	printf("\nexternal storage class\n");
	printf("------------------------\n");
	external_storage_class();
	external_storage_class();

  return 0;
}


void
automatic_storage_class(void)
{
	auto int x;  /* garbage value */
#if (GCC)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wuninitialized"
  assert(x == x);
# pragma GCC diagnostic pop
#endif

	auto int i = 0x1122;

  {
		auto int i = 0x3344;
    assert(0x3344 == i);
	}
  assert(0x1122 == i);
}


void
array_decay(char *restrict a)
{
	assert(a[0] == 0x11);
}


void
register_storage_class(register int x)
{
	register int  i;

  i = x;
	assert(i == x);

	/* error: address of register variable requested */
	/* int *p = &i; */

	register char  a[]  =  { 0x11, 0x22, 0x33, 0x44, };
  assert(sizeof(a)/sizeof(*a) == 4);


#if !(GCC && LINUX)
	array_decay(a);
#endif  /* error: address of register variable ‘a’ requested */
}


void
static_storage_class(void)
{
	static int  i  =  0;

  {
    static int  x;
		static int  i  =  0x11223344;

    x = i;
    f_int = 0;

    assert(x == i);
    (void) x;

    f_int++;
    i++;
	}

  i++;
  assert(i >= f_int);
}


/* definition for external linkage */
int g_var_x = 0x1122;


void
external_storage_class(void)
{
	extern int g_var_x;
  extern int g_var_y;
  extern int external_sum(int, int);

	printf("g_var_x = 0x%x\n", g_var_x++);
  printf("g_var_y = 0x%x\n", g_var_y);
  printf("sum(0x%x, 0x%x) = 0x%x\n", g_var_x,
         g_var_y, external_sum(g_var_x, g_var_y));
}
