#include <libgccjit.h>
#include <stdlib.h>
#include <stdio.h>


/*
   Let's try to inject the equivalent of:
   int
   sqr(int n)
   {
     return n * n;
   }
*/


static void create_sqr_fn (gcc_jit_context *);


int
main (int argc, char **argv)
{
  int               n;
  gcc_jit_context  *ctxt;
  gcc_jit_result   *result;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <integer>\n", argv[0]);
      exit(EXIT_FAILURE);
    }

  n = atoi(argv[1]);

  ctxt = gcc_jit_context_acquire();
  if (!ctxt)
    {
      fprintf(stderr, "NULL ctxt");
      exit(EXIT_FAILURE);
    }

  gcc_jit_context_set_bool_option(ctxt,
                                  GCC_JIT_BOOL_OPTION_DUMP_GENERATED_CODE,
                                  0);

  create_sqr_fn(ctxt);

  result = gcc_jit_context_compile(ctxt);
  if (!result)
    {
      fprintf(stderr, "NULL result");
      exit(EXIT_FAILURE);
    }

  typedef int (*fn_type) (int);
  fn_type sqr = (fn_type) gcc_jit_result_get_code(result, "sqr");
  if (!sqr)
    {
      fprintf(stderr, "NULL sqr");
      exit(EXIT_FAILURE);
    }

  printf("sqr(%i) = %i\n", n, sqr(n));

  gcc_jit_context_release(ctxt);
  gcc_jit_result_release(result);

  exit(EXIT_SUCCESS);

}


static void
create_sqr_fn(gcc_jit_context *ctxt)
{
  gcc_jit_type *int_type = gcc_jit_context_get_type(ctxt, GCC_JIT_TYPE_INT);

  gcc_jit_param *param_n
    = gcc_jit_context_new_param(ctxt, NULL, int_type, "n");

  gcc_jit_function *func
    = gcc_jit_context_new_function(ctxt, NULL,
                                   GCC_JIT_FUNCTION_EXPORTED,
                                   int_type,
                                   "sqr",
                                   1, &param_n,
                                   0);

  gcc_jit_block *block = gcc_jit_function_new_block (func, NULL);

  gcc_jit_rvalue *expr
    = gcc_jit_context_new_binary_op(ctxt, NULL,
                                    GCC_JIT_BINARY_OP_MULT, int_type,
                                    gcc_jit_param_as_rvalue (param_n),
                                    gcc_jit_param_as_rvalue (param_n));

  gcc_jit_block_end_with_return(block, NULL, expr);

}
