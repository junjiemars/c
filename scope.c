#include <stdio.h>

/*
 * A good artical here: http://norswap.com/c_scope_duration_linkage/
 *
 * The scope of a declaration is the part of the code where the declaration is seen
 * and can be used.
 * Note that this says nothing about whether the object associated
 * to the declaration can be accessed from some other part of the code via another
 * declaration. We uniquely identify an object by its memory: the storage for a
 * variable or the function code.
 * Finally, note that a declaration in a nested scope can hide a declaration in
 * an outer scope; but only if one of two has no linkage.
 *
 * Duration indicates whether the object associated to the declaration persists
 * throughout the program's execution or whether it is allocated dynamically when
 * the declaration's scope is entered.
 *
 * Linkage is what determines if multiple declarations of the same object refer to
 * the same object, or to separate ones. Each declaration can only have one of
 * five storage class specifier: static, extern, auto, register and typedef.
 *
 * Scope:
 * ----------
 * 1) block scope: every variable or function declaration that appears inside a block
 * (including a function body) has block scope. The scope goes from the declaration to
 * the end of the innermost block in which the declaration appears. Function parameter
 * declarations in function definitions (but not in prototypes) also have block scope.
 * The scope of a parameter declaration therefore includes the parameter declarations
 * that appears after it.
 *
 * 2) function scope: goto label is a bit special, which are implicitly declared at
 * the place where they appears, but they are visible throughout the function, even
 * if they appear inside a block.
 *
 * 3) function prototype scope: is the scope for function parameters that appears
 * inside a function prototype. It extends until the end of the prototype. This
 * scope exists to ensure that function parameters have distinct names.
 *
 * 4) file scope: all vairables and functions defined ouside functions have file
 * scope. They are visible from their declarration until the end of the file.
 * Here, the term 'file' should be understood as the source file being compiled,
 * after all includes have been resolved.
 * 
 * Storage Class Specifiers
 * ----------
 * 1) auto: can't apply to parameter declarations. It is the default for variable
 * declared inside a function body, and is in fact a historic leftover from C
 * predecessor's B.
 * 2) register: is a hint to the compiler that it might be a good idea to store
 * the variable in a register, but the compiler is not forced to do so. The
 * compiler does make sure that you do not take the address of a vairable with
 * the register storage class.
 *
 * A. automatic variables:
 * 1) automatic variables includes global_auto_i0/i1, i0/i1;
 * 2) uninitialized variables will be set to 0;
 *
 * 
 */

/* int global_auto_i0 = 123; */
/* int global_auto_i1; */
/* static int file_scope_i0 = 345; */
/* static int file_scope_i1; */

/* file scope  */
int i0 = 123;

/* function sub forward declaration */
void sub(int, int);

int main(int argc, char *argv[]) {
  /* file scope i0 */
  printf("file scope: i0=%i\n", i0);
  
  /* block scope in main */
  int i0 = 321;
  printf("function scope in main: i0=%i\n", i0);

  {
    int i0 = 123+321;
    printf("block scope in main function: i0=%i\n", i0);
  }

  /* block scope in main again */
  printf("block scope in main: i0=%i\n", i0);

  /* function parameters also has block scope */
  printf("function parameter also has block scope: argc=%i\n", argc);
  {
    int argc = 123;
    printf("function parameter also has block scope: argc=%i\n", argc);
  }

  if (i0 > 0) {
    goto i0;
    printf("this line bypassed via goto\n");
  }
  
  {
    /* goto lable has different namespace than objects,
     * so u can use i0 here
     */
    i0:
    printf("goto labe i0 inside inner block\n");
  }

  sub(i0, i0+1);

  {
    auto int i0 = 1;
    printf("auto int i0 inside anther block: i0=%i\n", i0);
  }
    /* int i1; */
    /* static int static_i0 = 234; */
    /* static int static_i1; */

    /* printf("i0=%i i1=%i\n", i0, i1); */
    /* printf("global_auto_i0=%i global_auto_i1=%i\n", global_auto_i0, global_auto_i1); */
    /* printf("static_i0=%i static_i1=%i\n", static_i0, static_i1); */
    /* printf("file_scope_i0=%i file_scope_i1=%i\n", file_scope_i0, file_scope_i1); */

}

void sub(int i0, int i1) {
  printf("block scope in sub: i0=%i\n", i0+i1);

  /* well, the i0 from function parameter i0, so u can't redefined it */
  /* int i0 += 1; */
}
