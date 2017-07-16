
lang: enum \
			env \
			fn \
			stage
lang_test: enum_test \
					 env_test \
					 fn_test \
					 stage_test

INC += -I$(src_path)
ifneq ($(NM_SYSTEM), MSYS_NT)
CFLAGS += -std=c99
endif


# enum 
enum_binout := $(bin_path)enum$(bin_ext)
enum_cppout := $(tmp_path)enum$(cpp_ext)

enum: $(enum_binout)
enum_test: enum
	$(enum_binout)

$(enum_binout): $(enum_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(enum_cppout): $(src_path)enum/e.c
	$(CPP) $(CPPFLAGS) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

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
	$(CAS) $(nm_stage_asm) $^ $(asm_out)$@

$(stage_cppout): $(src_path)stage/s.c
	$(CPP) $(CFLAGS) $(nm_stage_pre) $(INC) $^ > $@
