#include <nore.h>
#include <ndef.h>
#include <libgccjit.h>

#define MAX_OPS  64

typedef int (*asm_code)(int);

struct asm_fn
{
  gcc_jit_result  *af_result;
  asm_code         af_code;
};

struct asm_state
{
  gcc_jit_context   *ctxt;

  gcc_jit_type      *int_type;
  gcc_jit_type      *bool_type;
  gcc_jit_type      *stack_type;

  gcc_jit_rvalue    *const_1;

  gcc_jit_lvalue    *stack_top;
  gcc_jit_function  *fn;
  gcc_jit_param     *arg;
  gcc_jit_lvalue    *x;
  gcc_jit_lvalue    *y;

  gcc_jit_block     *init_block;
  gcc_jit_location  *op_locs[MAX_OPS];
  gcc_jit_block     *op_blocks[MAX_OPS];
};


/* static void add_push(struct asm_state*, gcc_jit_block*, */
/*                      gcc_jit_rvalue*, gcc_jit_location*); */

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);
  return 0;
}


/* void */
/* add_push(struct asm_state *state, gcc_jit_block *block, */
/*          gcc_jit_rvalue *rvalue, gcc_jit_location *loc) */
/* { */
/*   gcc_jit_block_add_assignment */
/*     (block, */
/*      loc, */

/*      gcc_jit_context_new_array_access */
/*      (state->ctxt, */
/*       loc, */
/*       gcc_jit_lvalue_as_rvalue(state->stack), */
/*       gcc_jit_lvalue_as_rvalue(state->statck_top)), */

/*      rvalue); */

/* } */
