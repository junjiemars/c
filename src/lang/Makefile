
lang: array					\
			assert				\
			enum					\
			env						\
			fn						\
			goto					\
			macro					\
			main					\
			scope					\
			sizeof				\
			stage					\
			type	

lang_test: 	array_test					\
						assert_test					\
						enum_test						\
						env_test						\
						fn_test							\
						goto_test						\
						macro_test					\
						main_test						\
						scope_test					\
						sizeof_test					\
						stage_test					\
						type_test

INC += -I$(src_path)


# array
array_binout := $(bin_path)array$(bin_ext)

array: $(array_binout)
array_test: array
	$(array_binout)

$(array_binout): $(src_path)array/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# assert at runtime
# static_assert at compile time
# ./configure --without-debug --has-lang
assert_binout := $(bin_path)assert$(bin_ext)

assert: $(assert_binout)
assert_test: assert
		-$(assert_binout) 0
		-$(assert_binout) 100
		-$(assert_binout) 49

$(assert_binout): $(src_path)assert/a.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# enum 
enum_binout := $(bin_path)enum$(bin_ext)
enum_cppout := $(tmp_path)enum$(cpp_ext)

enum: $(enum_binout)
enum_test: enum
	$(enum_binout)

$(enum_binout): $(enum_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(enum_cppout): $(src_path)enum/e.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

# env
env_binout := $(bin_path)env$(bin_ext)
env_cflags := $(CFLAGS) $(INC) -I$(src_path)env/

$(env_binout): $(src_path)env/env.c
	$(CC) $(env_cflags) $^ $(bin_out)$@ 

env: $(env_binout)
env_test: env
	$(env_binout) --COUNT=2 --TEXT=Bonjour
	COUNT=2 $(env_binout)
	COUNT=3 TEXT="Bonjor" $(env_binout)
	COUNT=2 $(env_binout) --TEXT=Bonjour

# fn
fn_binout := $(bin_path)fn$(bin_ext)

fn: $(fn_binout)
fn_test: fn
	$(fn_binout)

$(fn_binout): $(src_path)fn/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# goto
goto_binout := $(bin_path)goto$(bin_ext)

goto: $(goto_binout)
goto_test: goto
	$(goto_binout)

$(goto_binout): $(src_path)goto/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# macro
macro_binout := $(bin_path)macro$(bin_ext)
macro_cppout := $(tmp_path)macro$(cpp_ext)

macro: $(macro_binout)
macro_test: macro
	$(macro_binout)

macro_cflags += $(cflags) $(inc) -i$(src_path)

$(macro_binout): $(macro_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(macro_cppout): $(src_path)macro/macro.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# main
main_binout := $(bin_path)main$(bin_ext)

main: $(main_binout)
main_test: main
	$(main_binout) a bb ccc 

$(main_binout): $(src_path)main/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# scope
scope_binout := $(bin_path)scope$(bin_ext)

scope_cflags = $(CFLAGS)

ifeq ($(CC_NAME), msvc)
	scope_cflags += -Wv:18
endif

scope: $(scope_binout)
scope_test: scope
	$(scope_binout)

$(scope_binout): $(src_path)scope/scope.c
	$(CC) $(scope_cflags) $(INC) $^ $(bin_out)$@

# sizeof
sizeof_binout := $(bin_path)sizeof$(bin_ext)

sizeof: $(sizeof_binout)
sizeof_test: sizeof
	$(sizeof_binout)

$(sizeof_binout): $(src_path)sizeof/sizeof.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stage
stage_binout := $(bin_path)stage$(bin_ext)
stage_objout := $(tmp_path)stage$(obj_ext)
stage_asmout := $(tmp_path)stage$(asm_ext)
stage_cppout := $(tmp_path)stage$(cpp_ext)

stage: $(stage_binout)
stage_test: stage
	$(stage_binout)

$(stage_binout): $(stage_objout)
	$(LINK) $(LDFLAGS) $^ $(bin_out)$@

$(stage_objout): $(stage_asmout)
	$(AS) $(ASFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(stage_asmout): $(stage_cppout)
	$(CAS) $(CFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(stage_cppout): $(src_path)stage/s.c
	$(CPP) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

# type
type_binout := $(bin_path)type$(bin_ext)

type: $(type_binout)
type_test: type
	$(type_binout)

$(type_binout): $(src_path)type/t.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
