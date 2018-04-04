# ./configure --without-debug --has-lang

lang:	assert				\
			enum					\
			env						\
			exit          \
			fn						\
			goto					\
			jmp           \
			macro					\
			main					\
			pointer       \
			scope					\
			sizeof				\
			stage					\
			string        \
			type


lang_test:	assert_test					\
						enum_test						\
						env_test						\
            exit_test           \
						fn_test							\
						goto_test						\
            jmp_test            \
						macro_test					\
						main_test						\
						pointer_test        \
						scope_test					\
						sizeof_test					\
						stage_test					\
						string_test         \
						type_test


lang_prefix := lang
INC += -I$(lang_root)

# assert at runtime
# static_assert at compile time

assert_binout := $(bin_path)$(lang_prefix)_assert$(bin_ext)

assert: $(assert_binout)
assert_test: assert
		-$(assert_binout) 0
		-$(assert_binout) 100
		-$(assert_binout) 49

$(assert_binout): $(lang_root)assert/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# enum 
enum_binout := $(bin_path)$(lang_prefix)_enum$(bin_ext)
enum_cppout := $(tmp_path)$(lang_prefix)_enum$(cpp_ext)

enum: $(enum_binout)
enum_test: enum
	$(enum_binout)

$(enum_binout): $(enum_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(enum_cppout): $(lang_root)enum/e.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

# env
env_binout := $(bin_path)$(lang_prefix)_env$(bin_ext)
env_cflags := $(CFLAGS) $(INC) -I$(lang_root)env/

$(env_binout): $(lang_root)env/env.c $(lang_root)env/env.h
	$(CC) $(env_cflags) $< $(bin_out)$@ 

env: $(env_binout)
env_test: env
	$(env_binout) --COUNT=2 --TEXT=Bonjour
	COUNT=2 $(env_binout)
	COUNT=3 TEXT="Bonjor" $(env_binout)
	COUNT=2 $(env_binout) --TEXT=Bonjour

# exit
exit_binout := $(bin_path)$(lang_prefix)_exit$(bin_ext)
exit_no_fn_binout := $(bin_path)$(lang_prefix)_exit_no_fn$(bin_ext)

exit: $(exit_binout) $(exit_no_fn_binout)
exit_test: exit
	$(exit_binout)
	$(exit_no_fn_binout)

$(exit_binout): $(lang_root)exit/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(exit_no_fn_binout): $(lang_root)exit/exit_no_fn.c
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
jmp_binout := $(bin_path)$(lang_prefix)_jmp$(bin_ext)

jmp: $(jmp_binout)
jmp_test: jmp
	$(jmp_binout)

$(jmp_binout): $(lang_root)jmp/j.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# macro
macro_binout := $(bin_path)$(lang_prefix)_macro$(bin_ext)
macro_cppout := $(tmp_path)$(lang_prefix)_macro$(cpp_ext)

macro: $(macro_binout)
macro_test: macro
	$(macro_binout)

macro_cflags += $(cflags) $(inc) -i$(lang_root)

$(macro_binout): $(macro_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(macro_cppout): $(lang_root)macro/macro.c
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

# sizeof
sizeof_binout := $(bin_path)sizeof$(bin_ext)

sizeof: $(sizeof_binout)
sizeof_test: sizeof
	$(sizeof_binout)

$(sizeof_binout): $(lang_root)sizeof/sizeof.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stage
ifneq ($(CC_NAME), msvc)
stage_binout := $(bin_path)stage$(bin_ext)
stage_objout := $(tmp_path)stage$(obj_ext)
stage_asmout := $(tmp_path)stage$(asm_ext)
stage_cppout := $(tmp_path)stage$(cpp_ext)

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
	$(CAS) $(CFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(stage_cppout): $(lang_root)stage/s.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

else
stage:
stage_test:
stage_ldflags := -link -FORCE:MULTIPLE
endif


# string
string_basic_binout := $(bin_path)$(lang_prefix)_string_basic$(bin_ext)

string_basic_test: $(string_basic_binout)
	$(string_basic_binout)

string: $(string_basic_binout)
string_test: $(string_basic_test)

$(string_basic_binout): $(lang_root)string/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# type
type_binout := $(bin_path)type$(bin_ext)

type: $(type_binout)
type_test: type
	$(type_binout)

$(type_binout): $(lang_root)type/t.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

