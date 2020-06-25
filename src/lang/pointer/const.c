#include <_lang_.h>
#include <stdio.h>

void
test_ptr_to_const_obj(void) {
  int v1 = 0x11223344;
	const int *p1 = &v1;

  /* read-only variable is not assignable */
  /* *p1 += 1; */

	**(int**)&p1 += 1;

	printf("%32s: p1@%p = 0x%x\n", "const int *p1", p1, *p1);
}

void
test_const_ptr_to_obj(void) {
  int v1 = 0x11223344;
  int *const p1 = &v1;

  /* object is not const */
  *p1 += 1;

  /* cannot assign to variable 'p1' with const-qualified type 'int *const' */
  /* int v2 = 0x44332211; */
  /* p1 = &v2; */
  
  **(int**)&p1 += 1;

  printf("%32s: p1@%p = 0x%x\n", "int *const p1", p1, *p1);
}

void
test_const_ptr_to_const_obj(void) {
  int v1 = 0x11223344;
  const int *const p1 = &v1;

  **(int**)&p1 += 1;
  
  printf("%32s: p1@%p = 0x%x\n", "const int *const p1", p1, *p1);
}

void
test_ptr_to_ptr_to_const_obj(void) {
  int v1 = 0x1122;
  int *p1 = &v1;
  const int **p2 = (const int **)&p1;

  int v2 = 0x3344;
  int *p3 = &v2;
  p2 = (const int **)&p3;

  /* read-only variable is not assignable */
  /* **p2 += 1; */

  printf("%32s: p2@%p = 0x%x\n", "const int **p2", p2, **p2);
}

void
test_ptr_to_const_ptr_to_const_obj(void) {
  int v1 = 0x1122;
  int *p1 = &v1;
  const int *const *p2 = (const int *const *)&p1;

  int v2 = 0x3344;
  int *p3 = &v2;
  p2 = (const int *const *)&p3;

  /* read-only variable is not assignable */
  /* *p2 = p3; */
  /* **p2 += 1; */

  printf("%32s: p2@%p = 0x%x\n", "const int *const *p2", p2, **p2);
}

void
test_const_ptr_to_ptr_to_const_obj(void) {
  int v1 = 0x1122;
  int *p1 = &v1;
  const int **const p2 = (const int **const)&p1;

  int v2 = 0x3344;
  int *p3 = &v2;
  *p2 = p3;

  /* cannot assign to variable 'p2' with const-qualified type */
  /*     'const int **const' */
  /* p2 = (const int **const)&p3; */

  /* read-only variable is not assignable */
  /* **p2 += 1; */

  printf("%32s: p2@%p = 0x%x\n", "const int **const p2", p2, **p2);
}

void
test_const_ptr_to_const_ptr_to_obj(void) {
  int v1 = 0x1122;
  int *p1 = &v1;
  int *const *const p2 = (int *const *const)&p1;

  **p2 += 1;

  /* cannot assign to variable 'p2' with const-qualified */
  /*     type 'int *const *const' */
  /* int v2 = 0x3344; */
  /* int *p3 = &v2; */
  /* p2 = (int *const *const)&p3; */

  printf("%32s: p2@%p = 0x%x\n", "int *const *const p2", p2, **p2);
}

int 
main(void){
	printf("----------\n");

  test_ptr_to_const_obj();
  test_const_ptr_to_obj();
  test_const_ptr_to_const_obj();
  test_ptr_to_ptr_to_const_obj();
  test_ptr_to_const_ptr_to_const_obj();
  test_const_ptr_to_ptr_to_const_obj();
  test_const_ptr_to_const_ptr_to_obj();

  return 0;
}
