#include <_lang_.h>


/* C4456: declaration of 'i' hides previous local declaration */
#if (MSVC)
#  pragma warning(disable:4456)
#endif


static int f_int;

void automatic_storage_class(void);
static void static_storage_class_fn(void);
static int static_storage_class_fn_raw(int);
void array_decay(char *);
void external_storage_class(void);

void
automatic_storage_class(void)
{
	auto int x; /* garbage value */
#if (GCC)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wuninitialized"
  assert(x == x);
# pragma GCC diagnostic pop
#else
  _unused_(x);
#endif

	auto int i = 0x1122;

  {
		auto int i = 0x3344;
    assert(0x3344 == i);
	}
  assert(0x1122 == i);
}


void
array_decay(char *a)
{
	printf("a[0] = 0x%02x\n", a[0]);
}


void
register_storage_class(register int x)
{
	register int i;
  i = x;
	printf("i = 0x%08x\n", i++);
	/* error: address of register variable requested */
	/* int *p = &i; */

	register char a[] =
    { 0x11, 0x22, 0x33, 0x44, };
#if MSVC
	printf("a[0/%zu]\n", sizeof(a));
#elif CLANG || GCC
	printf("a[0/%zu] = 0x%02x\n", sizeof(a)/sizeof(a[0]), a[0]);
# if CLANG
	/* GCC error: address of register variable ‘a’ requested */
	array_decay(a);
# endif
#endif
}


void
static_storage_class_fn(void)
{
	static int i;

  {
    static int x;
    x = i;
		static int i = 0x11223344;
    assert((0x11223344 + x) == i);
    i++;
	}
  assert((0 + i) == f_int);
  f_int++;
  i++;
}

int
static_storage_class_fn_raw(int x)
{
  static int v;
  assert(0 == v);
  v += x;
  return v;
}

/* definition for external linkage */
int g_var_x = 0x1122;

void
external_storage_class(void)
{
	extern int g_var_x;
  extern int g_var_y;
	printf("g_var_x = 0x%08x\n", g_var_x++);
  printf("g_var_y = 0x%08x\n", g_var_y);
}


int
main(int argc, _unused_(char *argv[]))
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
	static_storage_class_fn();
	static_storage_class_fn();
	static_storage_class_fn();
  static_storage_class_fn_raw(argc);

	printf("\nexternal storage class\n");
	printf("------------------------\n");
	external_storage_class();
	external_storage_class();

  return 0;
}
