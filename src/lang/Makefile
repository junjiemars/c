
lang: enum \
			stage
lang_test: enum_test \
					 stage_test

INC += -I$(src_path)


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
