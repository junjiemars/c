# ./configure --without-debug --has-lang

lang: array										\
	  assert									\
	  duration									\
	  enum										\
	  env										\
	  error										\
	  exit										\
	  fn										\
	  goto										\
	  jmp										\
	  linkage									\
	  macro										\
	  main										\
	  math										\
	  random									\
	  lang_restrict								\
	  pointer									\
	  lang_preprocessor							\
	  scope										\
	  lang_signal								\
	  sizeof									\
	  stage										\
	  storage									\
	  string									\
	  lang_time									\
	  type										\
	  typedef									\
	  typeof									\
	  volatile


lang_test:  array_test							\
			assert_test							\
			duration_test						\
			enum_test							\
			env_test							\
			error_test							\
            exit_test							\
			fn_test								\
			goto_test							\
            jmp_test							\
			linkage_test						\
			macro_test							\
			main_test							\
			math_test							\
			random_test							\
			lang_restrict_test					\
			pointer_test						\
			lang_preprocessor_test				\
			scope_test							\
			lang_signal_test					\
			sizeof_test							\
			stage_test							\
			storage_test						\
			string_test							\
			lang_time_test						\
			type_test							\
			typedef_test						\
			typeof_test							\
			volatile_test


lang_prefix := lang
INC += -I$(lang_root)

_ERROR_ ?= 0

# array
array_binout := $(bin_path)$(lang_prefix)_array$(bin_ext)

array: $(array_binout)
array_test: array
	$(array_binout)

$(array_binout): $(lang_root)array/a1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# assert at runtime
# static_assert at compile time

assert_binout := $(bin_path)$(lang_prefix)_assert$(bin_ext)
assert_cppout := $(tmp_path)$(lang_prefix)_assert$(cpp_ext)

assert: $(assert_binout)
assert_test: assert
		-$(assert_binout) 49

$(assert_binout): $(assert_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(assert_cppout): $(lang_root)assert/a.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# duration
duration_binout := $(bin_path)$(lang_prefix)_duration$(bin_ext)
duration_extern_objout := $(bin_path)$(lang_prefix)_duration_extern$(obj_ext)
duration_d_objout := $(bin_path)$(lang_prefix)_duration_d$(obj_ext)

duration: $(duration_binout)
duration_test: duration
	$(duration_binout)

$(duration_binout): $(duration_extern_objout) $(duration_d_objout)
	$(LINK) $^ $(bin_out)$@

$(duration_extern_objout): $(lang_root)duration/extern.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(duration_d_objout): $(lang_root)duration/d.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# enum 
enum_binout := $(bin_path)$(lang_prefix)_enum$(bin_ext)
enum_cppout := $(tmp_path)$(lang_prefix)_enum$(cpp_ext)

enum: $(enum_binout)
enum_test: enum
	$(enum_binout)

$(enum_binout): $(enum_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(enum_cppout): $(lang_root)enum/e.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# env
env_var_binout := $(bin_path)$(lang_prefix)_env_var$(bin_ext)

$(env_var_binout): $(lang_root)env/var/var.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@ 

env: $(env_var_binout)
env_test: env
	$(env_var_binout) --COUNT=2 --TEXT=Bonjour
	COUNT=2 $(env_var_binout)
	COUNT=3 TEXT="Bonjor" $(env_var_binout)
	COUNT=2 $(env_var_binout) --TEXT=Bonjour

# error
error_basic_binout := $(bin_path)$(lang_prefix)_error_basic$(bin_ext)

error: $(error_basic_binout)
error_test: error
	$(error_basic_binout) $(CURDIR)/Makefilex
	$(error_basic_binout) $(CURDIR)/Makefile

$(error_basic_binout): $(lang_root)error/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# exit
exit_binout := $(bin_path)$(lang_prefix)_exit$(bin_ext)

exit: $(exit_binout)
exit_test: exit
	$(exit_binout)

$(exit_binout): $(lang_root)exit/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# fn
fn_binout := $(bin_path)$(lang_prefix)_fn$(bin_ext)

fn: $(fn_binout)
fn_test: fn
	$(fn_binout)

$(fn_binout): $(lang_root)fn/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# goto
goto_binout := $(bin_path)$(lang_prefix)_goto$(bin_ext)

goto: $(goto_binout)
goto_test: goto
	$(goto_binout)

$(goto_binout): $(lang_root)goto/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# jmp
jmp_basic_binout := $(bin_path)$(lang_prefix)_jmp_basic$(bin_ext)
jmp_try_binout := $(bin_path)$(lang_prefix)_jmp_try$(bin_ext)
jmp_try_cppout := $(tmp_path)$(lang_prefix)_jmp_try$(cpp_ext)

jmp: $(jmp_basic_binout) $(jmp_try_binout)
jmp_test: jmp
	$(jmp_basic_binout)
	$(jmp_try_binout)

$(jmp_basic_binout): $(lang_root)jmp/j.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(jmp_try_binout): $(jmp_try_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(jmp_try_cppout): $(lang_root)jmp/try.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# linkage
linkage_binout := $(bin_path)$(lang_prefix)_linkage$(bin_ext)
linkage_a_objout := $(tmp_path)$(lang_prefix)_linkage_a$(obj_ext)
linkage_c_objout := $(tmp_path)$(lang_prefix)_linkage_c$(obj_ext)

linkage: $(linkage_binout)
linkage_test: linkage
	$(linkage_binout)

$(linkage_binout): $(linkage_a_objout) $(linkage_c_objout)
	$(LINK) $^ $(bin_out)$@

$(linkage_a_objout): $(lang_root)linkage/extern.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(linkage_c_objout): $(lang_root)linkage/c.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@


# macro
macro_binout := $(bin_path)$(lang_prefix)_macro$(bin_ext)
macro_cppout := $(tmp_path)$(lang_prefix)_macro$(cpp_ext)
macro_nested_binout := $(bin_path)$(lang_prefix)_macro_nested$(bin_ext)
macro_nested_cppout := $(tmp_path)$(lang_prefix)_macro_nested$(cpp_ext)

macro: $(macro_binout) $(macro_nested_binout)
macro_test: macro
	$(macro_binout)
	$(macro_nested_binout)

$(macro_binout): $(macro_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(macro_cppout): $(lang_root)macro/macro.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

$(macro_nested_binout): $(macro_nested_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(macro_nested_cppout): $(lang_root)macro/nested.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# main
main_binout := $(bin_path)$(lang_prefix)_main$(bin_ext)
main_envp_binout := $(bin_path)$(lang_prefix)_main_envp$(bin_ext)

main: $(main_binout) $(main_envp_binout)
main_test: main
	$(main_binout) a bb ccc
	ZZZ=xyz $(main_envp_binout)

$(main_binout): $(lang_root)main/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(main_envp_binout): $(lang_root)main/m_envp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# math
math_binout := $(bin_path)$(lang_prefix)_math$(bin_ext)

math: $(math_binout)
math_test: math
	$(math_binout)

$(math_binout): $(lang_root)math/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# random
random_binout := $(bin_path)$(lang_prefix)_random_raw$(bin_ext)
random_arc_binout := $(bin_path)$(lang_prefix)_random_arc$(bin_ext)
random_s_binout := $(bin_path)$(lang_prefix)_random_s$(bin_ext)

random: $(random_binout) \
				$(random_arc_binout) \
				$(random_s_binout)
random_test: random
	$(random_binout) 10
	$(random_binout) 10 -10 10
	$(random_arc_binout)
	$(random_arc_binout) 20
	$(random_s_binout)

$(random_binout): $(lang_root)random/r.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(random_arc_binout): $(lang_root)random/arc.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(random_s_binout): $(lang_root)random/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# restrict
lang_restrict_binout := $(bin_path)$(lang_prefix)_restrict$(bin_ext)

lang_restrict: $(lang_restrict_binout)
lang_restrict_test: lang_restrict
	$(lang_restrict_binout)

$(lang_restrict_binout): $(lang_root)restrict/r1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# pointer
pointer_basic_binout := $(bin_path)$(lang_prefix)_pointer_basic$(bin_ext)
pointer_const_binout := $(bin_path)$(lang_prefix)_pointer_const$(bin_ext)
pointer_fn_binout := $(bin_path)$(lang_prefix)_pointer_fn$(bin_ext)
pointer_size_binout := $(bin_path)$(lang_prefix)_pointer_size$(bin_ext)

pointer_void_binout := $(bin_path)$(lang_prefix)_pointer_void$(bin_ext)

pointer_basic_test: $(pointer_basic_binout)
	$(pointer_basic_binout)

pointer_const_test: $(pointer_const_binout)
	$(pointer_const_binout)

pointer_fn_test: $(pointer_fn_binout)
	$(pointer_fn_binout)

pointer_size_test: $(pointer_size_binout)
	$(pointer_size_binout)

pointer_void_test: $(pointer_void_binout)
	$(pointer_void_binout)

pointer: $(pointer_basic_binout) \
				 $(pointer_const_binout) \
				 $(pointer_size_binout) \
				 $(pointer_void_binout)

pointer_test: $(pointer_basic_test) \
							$(pointer_const_test) \
							$(pointer_size_test) \
							$(pointer_void_test)

$(pointer_basic_binout): $(lang_root)pointer/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(pointer_const_binout): $(lang_root)pointer/const.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(pointer_fn_binout): $(lang_root)pointer/fn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(pointer_size_binout): $(lang_root)pointer/size.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(pointer_void_binout): $(lang_root)pointer/void.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# preprocessor
lang_preprocessor_binout := $(bin_path)$(lang_prefix)_preprocessor$(bin_ext)
lang_preprocessor_cppout := $(tmp_path)$(lang_prefix)_preprocessor$(cpp_ext)

lang_preprocessor: $(lang_preprocessor_binout)
lang_preprocessor_test: lang_preprocessor
	$(lang_preprocessor_binout)

$(lang_preprocessor_binout): $(lang_preprocessor_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_preprocessor_cppout): $(lang_root)preprocessor/p.c
	$(CPP) $(CPPFLAGS) $(INC) -D_ERROR_=$(_ERROR_) $(nm_stage_pre) $^ $(cpp_out)$@

# scope
scope_binout := $(bin_path)$(lang_prefix)_scope$(bin_ext)

scope_cflags = $(CFLAGS)

ifeq ($(CC_NAME), msvc)
	scope_cflags += -Wv:18
endif

scope: $(scope_binout)
scope_test: scope
	$(scope_binout)

$(scope_binout): $(lang_root)scope/scope.c
	$(CC) $(scope_cflags) $(INC) $^ $(bin_out)$@


# signal
ifeq ($(NM_SYSTEM), Linux)
signal_cflags := $(CFLAGS)
signal_cflags += -D_DEFAULT_SOURCE
signal_cflags += -D_BSD_SOURCE
signal_cflags += -D_XOPEN_SOURCE
endif

lang_signal_basic_binout := $(bin_path)$(lang_prefix)_signal_basic$(bin_ext)
lang_signal_list_binout := $(bin_path)$(lang_prefix)_signal_list$(bin_ext)
lang_signal_fork_binout := $(bin_path)$(lang_prefix)_signal_fork$(bin_ext)

lang_signal: $(lang_signal_basic_binout) \
				     $(lang_signal_list_binout) \
	  				 $(lang_signal_fork_binout)
lang_signal_test: lang_signal
	$(lang_signal_basic_binout)
	$(lang_signal_list_binout)
	$(lang_signal_fork_binout)
lang_signal_basic_test: $(lang_signal_basic_binout)
	$(lang_signal_basic_binout)
lang_signal_list_test: $(lang_signal_list_binout)
	$(lang_signal_list_binout)
lang_signal_fork_test: $(lang_signal_fork_binout)
	$(lang_signal_fork_binout)

$(lang_signal_basic_binout): $(lang_root)signal/basic/sig.c
	$(CC) $(signal_cflags) $(INC) $^ $(bin_out)$@

$(lang_signal_list_binout): $(lang_root)signal/list/list-sig.c
	$(CC) $(signal_cflags) $(INC) $^ $(bin_out)$@

$(lang_signal_fork_binout): $(lang_root)signal/fork/f.c
	$(CC) $(signal_cflags) $(INC) $^ $(bin_out)$@

# sizeof
sizeof_binout := $(bin_path)sizeof$(bin_ext)

sizeof: $(sizeof_binout)
sizeof_test: sizeof
	$(sizeof_binout)

$(sizeof_binout): $(lang_root)sizeof/sizeof.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stage
ifneq ($(CC_NAME), msvc)
stage_binout := $(bin_path)$(lang_prefix)_stage$(bin_ext)
stage_objout := $(tmp_path)$(lang_prefix)_stage$(obj_ext)
stage_asmout := $(tmp_path)$(lang_prefix)_stage$(asm_ext)
stage_cppout := $(tmp_path)$(lang_prefix)_stage$(cpp_ext)

stage: $(stage_binout)
stage_test: stage
	$(stage_binout)

ifeq ($(NM_VERBOSE), YES)
stage_ldflags += -VERBOSE:LIB
endif

$(stage_binout): $(stage_objout)
	$(LINK) $^ $(bin_out)$@ $(stage_ldflags)

$(stage_objout): $(stage_asmout) 
	$(AS) $(ASFLAGS) $(obj_out)$@ $(nm_stage_c) $^

$(stage_asmout): $(stage_cppout)
	$(AS) $(CFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(stage_cppout): $(lang_root)stage/s.c
	$(CPP) $(CPPFLAGS) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

else
stage:
stage_test:
stage_ldflags := -link -FORCE:MULTIPLE
endif


# storage
storage_binout := $(bin_path)$(lang_prefix)_storage$(bin_ext)
storage_extern_objout := $(tmp_path)$(lang_prefix)_storage_extern$(obj_ext)
storage_s_objout := $(tmp_path)$(lang_prefix)_storage_s$(obj_ext)

storage: $(storage_binout)
storage_test: storage
	$(storage_binout)

$(storage_binout): $(storage_extern_objout) $(storage_s_objout)
	$(LINK) $^ $(bin_out)$@

$(storage_s_objout): $(lang_root)storage/s.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(storage_extern_objout): $(lang_root)storage/extern.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# string
ifeq ($(NM_SYSTEM), Linux)
string_cflags := $(CFLAGS)
string_cflags += -D_GNU_SOURCE
else
string_cflags = $(CFLAGS)
endif

string_basic_binout := $(bin_path)$(lang_prefix)_string_basic$(bin_ext)
string_n_binout := $(bin_path)$(lang_prefix)_string_n$(bin_ext)
string_s_binout := $(bin_path)$(lang_prefix)_string_s$(bin_ext)
string_dup_binout := $(bin_path)$(lang_prefix)_string_dup$(bin_ext)
string_tok_binout := $(bin_path)$(lang_prefix)_string_tok$(bin_ext)

string: $(string_basic_binout) \
        $(string_n_binout) \
        $(string_s_binout) \
        $(string_dup_binout) \
        $(string_tok_binout)

string_test: string_basic_test									\
             string_n_test											\
             string_s_test											\
             $(string_dup_binout)								\
             $(string_tok_binout)								\
             $(string_basic_binout)							\
             $(string_n_binout)									\
             $(string_s_binout)									\
             $(string_dup_binout)								\
             string_tok_test

string_basic_test: $(string_basic_binout)
	$(string_basic_binout)
string_n_test: $(string_n_binout)
	$(string_n_binout)
string_s_test: $(string_s_binout)
	$(string_s_binout)
string_tok_test: $(string_tok_binout)
	$(string_tok_binout) "this is a simple sample for strtok." " "

$(string_basic_binout): $(lang_root)string/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(string_n_binout): $(lang_root)string/n.c
	$(CC) $(string_cflags) $(INC) $^ $(bin_out)$@

$(string_s_binout): $(lang_root)string/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(string_dup_binout): $(lang_root)string/dup.c
	$(CC) $(string_cflags) $(INC) $^ $(bin_out)$@

$(string_tok_binout): $(lang_root)string/tok.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# time
lang_time_binout := $(bin_path)$(lang_prefix)_time$(bin_ext)
lang_clock_binout := $(bin_path)$(lang_prefix)_clock$(bin_ext)

lang_time: $(lang_time_binout) \
					 $(lang_clock_binout)
lang_time_test: lang_time
	$(lang_time_binout)
	$(lang_clock_binout)

$(lang_time_binout): $(lang_root)time/t.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_clock_binout): $(lang_root)time/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# type
type_binout := $(bin_path)$(lang_prefix)_type$(bin_ext)
type_cppout := $(tmp_path)$(lang_prefix)_type$(cpp_ext)

type: $(type_binout)
type_test: type
	$(type_binout)

$(type_binout): $(type_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(type_cppout): $(lang_root)type/t.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# typedef
typedef_binout := $(bin_path)$(lang_prefix)_typedef$(bin_ext)

typedef: $(typedef_binout)
typedef_test: typedef
	$(typedef_binout)

$(typedef_binout): $(lang_root)typedef/t.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# typeof
typeof_binout := $(bin_path)$(lang_prefix)_typeof$(bin_ext)

typeof: $(typeof_binout)
typeof_test: typeof
	$(typeof_binout)

$(typeof_binout): $(lang_root)typeof/to.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# volatile
volatile_basic_binout := $(bin_path)$(lang_prefix)_volatile_basic$(bin_ext)
volatile_pointer_binout := $(bin_path)$(lang_prefix)_volatile_pointer$(bin_ext)
volatile_struct_binout := $(bin_path)$(lang_prefix)_volatile_struct$(bin_ext)

volatile: $(volatile_basic_binout) \
					$(volatile_pointer_binout) \
					$(volatile_struct_binout)

volatile_test: volatile
	$(volatile_basic_binout)
	$(volatile_pointer_binout)
	$(volatile_struct_binout)

$(volatile_basic_binout): $(lang_root)volatile/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(volatile_pointer_binout): $(lang_root)volatile/pointer.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(volatile_struct_binout): $(lang_root)volatile/struct.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

