#
# ./configure --without-debug --has-lang
#

lang_prefix := lang
INC += -I$(root) -I$(lang_root)

_ERROR_ ?= 0
_MEMORY_ ?= 0

# CFLAGS += $(if $(strip $(nm_build_opt)),,$(cflags_sanitize))
ifeq ($(shell test -n "$(_MEMORY_)" && test $(_MEMORY_) -gt 0; echo $$?),0)
	CFLAGS += $(cflags_sanitize)
endif

lang: lang_array																\
      lang_assert																\
      lang_duration															\
      lang_enum																	\
      lang_env																	\
      lang_error																\
      lang_exit																	\
      lang_fn																		\
      lang_goto																	\
      lang_jmp																	\
      lang_linkage															\
      lang_locale																\
      lang_macro																\
      lang_main																	\
      lang_math																	\
      lang_pointer															\
      lang_preprocessor													\
      lang_random																\
      lang_restrict															\
      lang_scope																\
      lang_signal																\
      lang_sizeof																\
      lang_stage																\
      lang_storage															\
      lang_string																\
      lang_struct																\
      lang_time																	\
      lang_type																	\
      lang_typedef															\
      lang_typeof																\
      lang_union																\
      lang_volatile


lang_test:  lang_array_test											\
            lang_assert_test										\
            lang_duration_test									\
            lang_enum_test											\
            lang_env_test												\
            lang_error_test											\
            lang_exit_test											\
            lang_fn_test												\
            lang_goto_test											\
            lang_jmp_test												\
            lang_linkage_test										\
            lang_locale_test										\
            lang_macro_test											\
            lang_main_test											\
            lang_math_test											\
            lang_pointer_test										\
            lang_preprocessor_test							\
            lang_random_test										\
            lang_restrict_test									\
            lang_scope_test											\
            lang_signal_test										\
            lang_sizeof_test										\
            lang_stage_test											\
            lang_storage_test										\
            lang_string_test										\
            lang_struct_test										\
            lang_time_test											\
            lang_type_test											\
            lang_typedef_test										\
            lang_typeof_test										\
            lang_union_test											\
            lang_volatile_test


# array
lang_array_binout := $(bin_path)$(lang_prefix)_lang_array$(bin_ext)

lang_array: $(lang_array_binout)
lang_array_test: lang_array
	$(lang_array_binout)

$(lang_array_binout): $(lang_root)array/a1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# assert at runtime
# static_assert at compile time

lang_assert_binout := $(bin_path)$(lang_prefix)_assert$(bin_ext)
lang_assert_cppout := $(tmp_path)$(lang_prefix)_assert$(cpp_ext)

lang_assert: $(lang_assert_binout)
lang_assert_test: lang_assert
		-$(lang_assert_binout) 49

$(lang_assert_binout): $(lang_assert_cppout)
	$(CC) $(CFLAGS) -D_ASSERT_=1 $^ $(bin_out)$@

$(lang_assert_cppout): $(lang_root)assert/a.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# duration
lang_duration_binout := $(bin_path)$(lang_prefix)_duration$(bin_ext)
lang_duration_extern_objout := $(bin_path)$(lang_prefix)_duration_extern$(obj_ext)
lang_duration_d_objout := $(bin_path)$(lang_prefix)_duration_d$(obj_ext)

lang_duration: $(lang_duration_binout)
lang_duration_test: lang_duration
	$(lang_duration_binout)

$(lang_duration_binout): $(lang_duration_extern_objout) \
                         $(lang_duration_d_objout)
	$(LINK) $(CFLAGS) $^ $(bin_out)$@

$(lang_duration_extern_objout): $(lang_root)duration/extern.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(lang_duration_d_objout): $(lang_root)duration/d.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# enum 
lang_enum_binout := $(bin_path)$(lang_prefix)_enum$(bin_ext)
lang_enum_cppout := $(tmp_path)$(lang_prefix)_enum$(cpp_ext)

lang_enum: $(lang_enum_binout)
lang_enum_test: lang_enum
	$(lang_enum_binout)

$(lang_enum_binout): $(lang_enum_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_enum_cppout): $(lang_root)enum/e.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# env
lang_env_var_binout := $(bin_path)$(lang_prefix)_env_var$(bin_ext)

$(lang_env_var_binout): $(lang_root)env/var/var.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@ 

lang_env: $(lang_env_var_binout)
lang_env_test: lang_env
	$(lang_env_var_binout) --COUNT=2 --TEXT=Bonjour
	COUNT=2 $(lang_env_var_binout)
	COUNT=3 TEXT="Bonjor" $(lang_env_var_binout)
	COUNT=2 $(lang_env_var_binout) --TEXT=Bonjour

# error
lang_error_basic_binout := $(bin_path)$(lang_prefix)_error_basic$(bin_ext)

ifeq ($(NM_SYSTEM), Linux)
  error_cflags := $(CFLAGS)
  error_cflags += -D_POSIX_C_SOURCE=200112L
	error_lflags := $(LFLAGS)
	error_lflags += -lm
else
  error_cflags = $(CFLAGS)
	error_lflags = $(LFLAGS)
endif

lang_error: $(lang_error_basic_binout)
lang_error_test: lang_error
	$(lang_error_basic_binout) $(CURDIR)/Makefilex
	$(lang_error_basic_binout) $(CURDIR)/Makefile

$(lang_error_basic_binout): $(lang_root)error/e.c
	$(CC) $(error_cflags) $(INC) $^ $(bin_out)$@ $(error_lflags)

# exit
lang_exit_binout := $(bin_path)$(lang_prefix)_exit$(bin_ext)

lang_exit: $(lang_exit_binout)
lang_exit_test: lang_exit
	$(lang_exit_binout)

$(lang_exit_binout): $(lang_root)exit/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# fn
lang_fn_binout := $(bin_path)$(lang_prefix)_fn$(bin_ext)

lang_fn: $(lang_fn_binout)
lang_fn_test: lang_fn
	$(lang_fn_binout)

$(lang_fn_binout): $(lang_root)fn/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# goto
lang_goto_binout := $(bin_path)$(lang_prefix)_goto$(bin_ext)

lang_goto: $(lang_goto_binout)
lang_goto_test: lang_goto
	$(lang_goto_binout)

$(lang_goto_binout): $(lang_root)goto/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# jmp
lang_jmp_basic_binout := $(bin_path)$(lang_prefix)_jmp_basic$(bin_ext)
lang_jmp_try_binout := $(bin_path)$(lang_prefix)_jmp_try$(bin_ext)
lang_jmp_try_cppout := $(tmp_path)$(lang_prefix)_jmp_try$(cpp_ext)

lang_jmp: $(lang_jmp_basic_binout) $(lang_jmp_try_binout)
lang_jmp_test: lang_jmp
	$(lang_jmp_basic_binout)
	$(lang_jmp_try_binout)

$(lang_jmp_basic_binout): $(lang_root)jmp/j.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_jmp_try_binout): $(lang_jmp_try_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_jmp_try_cppout): $(lang_root)jmp/try.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# linkage
lang_linkage_lnkc_binout := $(bin_path)$(lang_prefix)_linkage_lnkc$(bin_ext)
lang_linkage_lnk_objout := $(tmp_path)$(lang_prefix)_linkage_lnk$(obj_ext)
lang_linkage_c_objout := $(tmp_path)$(lang_prefix)_linkage_c$(obj_ext)
lang_linkage_whole_binout := $(bin_path)$(lang_prefix)_linkage_whole$(bin_ext)

lang_linkage: $(lang_linkage_lnkc_binout)				\
              $(lang_linkage_whole_binout)
lang_linkage_test: lang_linkage_lnkc_test				\
                   lang_linkage_whole_test

lang_linkage_lnkc_test: $(lang_linkage_lnkc_binout)
	$(lang_linkage_lnkc_binout)
lang_linkage_whole_test: $(lang_linkage_whole_binout)
	$(lang_linkage_whole_binout)

$(lang_linkage_lnkc_binout): $(lang_linkage_lnk_objout)	\
                             $(lang_linkage_c_objout)
	$(LINK) $^ $(bin_out)$@

$(lang_linkage_whole_binout): $(lang_root)linkage/c.c \
                              $(lang_root)linkage/lnk.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_linkage_lnk_objout): $(lang_root)linkage/lnk.c	\
                            $(lang_root)linkage/lnk.h
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $< $(obj_out)$@

$(lang_linkage_c_objout): $(lang_root)linkage/c.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# locale
lang_locale_binout := $(bin_path)$(lang_prefix)_locale$(bin_ext)

lang_locale: $(lang_locale_binout)
lang_locale_test: lang_locale
	$(lang_locale_binout)

$(lang_locale_binout): $(lang_root)locale/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# macro
lang_macro_binout := $(bin_path)$(lang_prefix)_macro$(bin_ext)
lang_macro_cppout := $(tmp_path)$(lang_prefix)_macro$(cpp_ext)
lang_macro_nested_binout := $(bin_path)$(lang_prefix)_macro_nested$(bin_ext)
lang_macro_nested_cppout := $(tmp_path)$(lang_prefix)_macro_nested$(cpp_ext)

lang_macro: $(lang_macro_binout) $(lang_macro_nested_binout)
lang_macro_test: lang_macro
	$(lang_macro_binout)
	$(lang_macro_nested_binout)

$(lang_macro_binout): $(lang_macro_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_macro_cppout): $(lang_root)macro/macro.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

$(lang_macro_nested_binout): $(lang_macro_nested_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_macro_nested_cppout): $(lang_root)macro/nested.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# main
lang_main_binout := $(bin_path)$(lang_prefix)_main$(bin_ext)
lang_main_envp_binout := $(bin_path)$(lang_prefix)_main_envp$(bin_ext)

lang_main: $(lang_main_binout) $(lang_main_envp_binout)
lang_main_test: lang_main
	$(lang_main_binout) a bb ccc
	ZZZ=xyz $(lang_main_envp_binout)

$(lang_main_binout): $(lang_root)main/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_main_envp_binout): $(lang_root)main/m_envp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# math
lang_math_complex_binout := $(bin_path)$(lang_prefix)_math_complex$(bin_ext)
lang_math_fcmp_binout := $(bin_path)$(lang_prefix)_math_fcmp$(bin_ext)

lang_math: $(lang_math_complex_binout)					\
           $(lang_math_fcmp_binout)
lang_math_test: lang_math_complex_test					\
                lang_math_fcmp_test

lang_math_complex_test: $(lang_math_complex_binout)
	$(lang_math_complex_binout)
lang_math_fcmp_test: $(lang_math_fcmp_binout)
	$(lang_math_fcmp_binout)

math_inc := $(INC) -I$(root)posix

$(lang_math_complex_binout): $(lang_root)math/c.c
	$(CC) $(CFLAGS) $(math_inc) $^ $(bin_out)$@

$(lang_math_fcmp_binout): $(lang_root)math/fcmp.c
	$(CC) $(CFLAGS) $(math_inc) $^ $(bin_out)$@

# random
lang_random_binout := $(bin_path)$(lang_prefix)_random_raw$(bin_ext)
lang_random_arc_binout := $(bin_path)$(lang_prefix)_random_arc$(bin_ext)
lang_random_s_binout := $(bin_path)$(lang_prefix)_random_s$(bin_ext)

lang_random: $(lang_random_binout)							\
             $(lang_random_arc_binout)					\
             $(lang_random_s_binout)
lang_random_test: lang_random
	$(lang_random_binout) 10
	$(lang_random_binout) 10 -10 10
	$(lang_random_arc_binout)
	$(lang_random_arc_binout) 20
	$(lang_random_s_binout)

$(lang_random_binout): $(lang_root)random/r.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_random_arc_binout): $(lang_root)random/arc.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_random_s_binout): $(lang_root)random/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# restrict
lang_restrict_binout := $(bin_path)$(lang_prefix)_restrict$(bin_ext)

lang_restrict: $(lang_restrict_binout)
lang_restrict_test: lang_restrict
	$(lang_restrict_binout)

$(lang_restrict_binout): $(lang_root)restrict/r1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# pointer
lang_ptr_basic_binout := $(bin_path)$(lang_prefix)_ptr_basic$(bin_ext)
lang_ptr_const_binout := $(bin_path)$(lang_prefix)_ptr_const$(bin_ext)
lang_ptr_fn_binout := $(bin_path)$(lang_prefix)_ptr_fn$(bin_ext)
lang_ptr_size_binout := $(bin_path)$(lang_prefix)_ptr_size$(bin_ext)
lang_ptr_void_binout := $(bin_path)$(lang_prefix)_ptr_void$(bin_ext)
lang_ptr_lvalue_binout := $(bin_path)$(lang_prefix)_ptr_lvalue$(bin_ext)
lang_ptr_arith_binout := $(bin_path)$(lang_prefix)_ptr_arith$(bin_ext)

lang_pointer: lang_ptr_basic										\
	  					lang_ptr_const										\
              lang_ptr_fn												\
              lang_ptr_size											\
		  				lang_ptr_void											\
              lang_ptr_lvalue										\
              lang_ptr_arith

lang_pointer_test: lang_ptr_basic_test					\
							     lang_ptr_const_test					\
                   lang_ptr_fn_test							\
                   lang_ptr_size_test						\
                   lang_ptr_void_test						\
                   lang_ptr_lvalue							\
                   lang_ptr_arith

lang_ptr_basic: $(lang_ptr_basic_binout)
lang_ptr_basic_test: lang_ptr_basic
	$(lang_ptr_basic_binout)

lang_ptr_const: $(lang_ptr_const_binout)
lang_ptr_const_test: lang_ptr_const
	$(lang_ptr_const_binout)

lang_ptr_fn: $(lang_ptr_fn_binout)
lang_ptr_fn_test: lang_ptr_fn
	$(lang_ptr_fn_binout)

lang_ptr_size: $(lang_ptr_size_binout)
lang_ptr_size_test: lang_ptr_size
	$(lang_ptr_size_binout)

lang_ptr_void: $(lang_ptr_void_binout)
lang_ptr_void_test: lang_ptr_void
	$(lang_ptr_void_binout)

lang_ptr_lvalue: $(lang_ptr_lvalue_binout)
lang_ptr_lvalue_test: lang_ptr_lvalue
	$(lang_ptr_lvalue_binout)

lang_ptr_arith: $(lang_ptr_arith_binout)
lang_ptr_arith_test: lang_ptr_arith
	$(lang_ptr_arith_binout)

$(lang_ptr_basic_binout): $(lang_root)pointer/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_const_binout): $(lang_root)pointer/const.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_fn_binout): $(lang_root)pointer/fn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_size_binout): $(lang_root)pointer/size.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_void_binout): $(lang_root)pointer/void.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_lvalue_binout): $(lang_root)pointer/lvalue.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_arith_binout): $(lang_root)pointer/arith.c
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
lang_scope_binout := $(bin_path)$(lang_prefix)_scope$(bin_ext)

scope_cflags = $(CFLAGS)
ifeq ($(CC_NAME), msvc)
	scope_cflags += -Wv:18
endif

lang_scope: $(lang_scope_binout)
lang_scope_test: lang_scope
	$(lang_scope_binout)

$(lang_scope_binout): $(lang_root)scope/scope.c
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
lang_sizeof_binout := $(bin_path)sizeof$(bin_ext)

lang_sizeof: $(lang_sizeof_binout)
lang_sizeof_test: lang_sizeof
	$(lang_sizeof_binout)

$(lang_sizeof_binout): $(lang_root)sizeof/sizeof.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stage
ifneq ($(CC_NAME),msvc)
stage_binout := $(bin_path)$(lang_prefix)_stage$(bin_ext)
stage_objout := $(tmp_path)$(lang_prefix)_stage$(obj_ext)
stage_asmout := $(tmp_path)$(lang_prefix)_stage$(asm_ext)
stage_cppout := $(tmp_path)$(lang_prefix)_stage$(cpp_ext)

lang_stage: $(stage_binout)
lang_stage_test: lang_stage
	$(stage_binout)

$(stage_binout): $(stage_objout)
	$(LINK) $^ $(bin_out)$@ $(stage_ldflags)

$(stage_objout): $(stage_asmout) 
	$(AS) $(ASFLAGS) $(obj_out)$@ $(nm_stage_c) $^

$(stage_asmout): $(stage_cppout)
	$(AS) $(CFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(stage_cppout): $(lang_root)stage/s.c
	$(CPP) $(CPPFLAGS) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@

else
lang_stage:
lang_stage_test:
stage_ldflags := -link -FORCE:MULTIPLE
ifeq ($(NM_VERBOSE),YES)
stage_ldflags += -VERBOSE:LIB
endif
endif


# storage
lang_stor_binout := $(bin_path)$(lang_prefix)_storage$(bin_ext)
lang_stor_extern_objout := $(tmp_path)$(lang_prefix)_storage_extern$(obj_ext)
lang_stor_s_objout := $(tmp_path)$(lang_prefix)_storage_s$(obj_ext)

lang_storage: $(lang_stor_binout)
lang_storage_test: lang_storage
	$(lang_stor_binout)

$(lang_stor_binout): $(lang_stor_extern_objout) $(lang_stor_s_objout)
	$(LINK) $^ $(bin_out)$@

$(lang_stor_s_objout): $(lang_root)storage/s.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(lang_stor_extern_objout): $(lang_root)storage/extern.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# string
ifeq ($(NM_SYSTEM), Linux)
string_cflags := $(CFLAGS)
string_cflags += -D_GNU_SOURCE
else
string_cflags = $(CFLAGS)
endif

string_inc := $(INC) -I$(root)posix

lang_str_basic_binout := $(bin_path)$(lang_prefix)_string_basic$(bin_ext)
lang_str_n_binout := $(bin_path)$(lang_prefix)_string_n$(bin_ext)
lang_str_s_binout := $(bin_path)$(lang_prefix)_string_s$(bin_ext)
lang_str_dup_binout := $(bin_path)$(lang_prefix)_string_dup$(bin_ext)
lang_str_tok_binout := $(bin_path)$(lang_prefix)_string_tok$(bin_ext)
lang_str_chr_binout := $(bin_path)$(lang_prefix)_string_chr$(bin_ext)
lang_str_pbrk_binout := $(bin_path)$(lang_prefix)_string_pbrk$(bin_ext)
lang_str_spn_binout := $(bin_path)$(lang_prefix)_string_spn$(bin_ext)

lang_string: lang_str_basic											\
             lang_str_n													\
             lang_str_s													\
             lang_str_dup												\
             lang_str_tok												\
             lang_str_chr												\
             lang_str_pbrk											\
             lang_str_spn

lang_string_test: lang_str_basic_test						\
                  lang_str_n_test								\
                  lang_str_s_test								\
                  lang_str_dup_test							\
                  lang_str_tok_test							\
                  lang_str_chr_test							\
                  lang_str_pbrk_test						\
                  lang_str_spn_test

lang_str_basic: $(lang_str_basic_binout)
lang_str_basic_test: lang_str_basic
	$(lang_str_basic_binout)

lang_str_n: $(lang_str_n_binout)
lang_str_n_test: lang_str_n
	$(lang_str_n_binout) "abcd1234" "abcd" "4"
	$(lang_str_n_binout) "abcd1234" "abcd1" "4"
	$(lang_str_n_binout) "abcd1234" "abcde" "5"
	$(lang_str_n_binout) "abcd1234" "abcde" "0"
	$(lang_str_n_binout) "abcd1234" "abcd" "10"

lang_str_s: $(lang_str_s_binout)
lang_str_s_test: lang_str_s
	$(lang_str_s_binout)

lang_str_dup: $(lang_str_dup_binout)
lang_str_dup_test: lang_str_dup
	$(lang_str_dup_binout) "the quick brown fox"

lang_str_tok: $(lang_str_tok_binout)
lang_str_tok_test: lang_str_tok
	$(lang_str_tok_binout) "this is a simple sample for strtok." " ."
	$(lang_str_tok_binout) "this is a simple    sample for strtok." " ."

lang_str_chr: $(lang_str_chr_binout)
lang_str_chr_test: lang_str_chr
	$(lang_str_chr_binout) "the quick brown fox jumps over the lazy dog" "j"
	$(lang_str_chr_binout) "the quick brown fox jumps over the lazy dog" "t"
	$(lang_str_chr_binout) "the quick brown fox jumps over the lazy dog" "1"

lang_str_pbrk: $(lang_str_pbrk_binout)
lang_str_pbrk_test: lang_str_pbrk
	$(lang_str_pbrk_binout) "the quick brown fox jumps over the lazy dog" "fxx"
	$(lang_str_pbrk_binout) "the quick brown fox jumps over the lazy dog" "dxx"
	$(lang_str_pbrk_binout) "the quick brown fox jumps over the lazy dog" "123"

lang_str_spn: $(lang_str_spn_binout)
lang_str_spn_test: lang_str_spn
	$(lang_str_spn_binout) "the quick brown fox jumps over the lazy dog" "f"
	$(lang_str_spn_binout) "the quick brown fox jumps over the lazy dog" "q"
	$(lang_str_spn_binout) "the quick brown fox jumps over the lazy dog" "the q"
	$(lang_str_spn_binout) "the quick brown fox jumps over the lazy dog" "fthe q"
	$(lang_str_spn_binout) "the quick brown fox jumps over the lazy dog" "fthe x"

$(lang_str_basic_binout): $(lang_root)string/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_str_n_binout): $(lang_root)string/n.c
	$(CC) $(string_cflags) $(INC) $^ $(bin_out)$@

$(lang_str_s_binout): $(lang_root)string/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_str_dup_binout): $(lang_root)string/dup.c
	$(CC) $(string_cflags) $(INC) $^ $(bin_out)$@

$(lang_str_tok_binout): $(lang_root)string/tok.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_str_chr_binout): $(lang_root)string/chr.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_str_pbrk_binout): $(lang_root)string/pbrk.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_str_spn_binout): $(lang_root)string/spn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# struct
lang_struct_binout := $(bin_path)$(lang_prefix)_struct$(bin_ext)

lang_struct: $(lang_struct_binout)
lang_struct_test: lang_struct
	$(lang_struct_binout)

$(lang_struct_binout): $(lang_root)struct/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# time
lang_time_basic_binout := $(bin_path)$(lang_prefix)_time_basic$(bin_ext)
lang_time_clock_binout := $(bin_path)$(lang_prefix)_time_clock$(bin_ext)
lang_time_conv_binout := $(bin_path)$(lang_prefix)_time_conv$(bin_ext)

lang_time: $(lang_time_basic_binout)						\
					 $(lang_time_clock_binout)						\
           $(lang_time_conv_binout)
lang_time_test: lang_time_basic_test						\
                lang_time_clock_test						\
                lang_time_conv_test

lang_time_basic_test: $(lang_time_basic_binout)
	$(lang_time_basic_binout)
lang_time_clock_test: $(lang_time_clock_binout)
	$(lang_time_clock_binout) 65536
lang_time_conv_test: $(lang_time_conv_binout)
	$(lang_time_conv_binout) 1594560256

lang_time_conv_test: $(lang_time_conv_binout)

$(lang_time_basic_binout): $(lang_root)time/bt.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_time_clock_binout): $(lang_root)time/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_time_conv_binout): $(lang_root)time/conv.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# type
lang_type_int_binout := $(bin_path)$(lang_prefix)_type_int$(bin_ext)
lang_type_c_binout := $(bin_path)$(lang_prefix)_type_c$(bin_ext)

lang_type: $(lang_type_int_binout)						\
           $(lang_type_c_binout)
lang_type_test: lang_type_int_test						\
                lang_type_c_test

lang_type_int_test: $(lang_type_int_binout)
	$(lang_type_int_binout)
lang_type_c_test: $(lang_type_c_binout)
	$(lang_type_c_binout) 11ff22aa

$(lang_type_int_binout): $(lang_root)type/int.c
	$(CPP) $(INC) $(CFLAGS) $^ $(bin_out)$@

$(lang_type_c_binout): $(lang_root)type/ct.c
	$(CC) $(INC) $(CFLAGS) $^ $(bin_out)$@


# typedef
lang_typedef_binout := $(bin_path)$(lang_prefix)_typedef$(bin_ext)

lang_typedef: $(lang_typedef_binout)
lang_typedef_test: lang_typedef
	$(lang_typedef_binout)

$(lang_typedef_binout): $(lang_root)typedef/t.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# typeof
lang_typeof_binout := $(bin_path)$(lang_prefix)_typeof$(bin_ext)

lang_typeof: $(lang_typeof_binout)
lang_typeof_test: lang_typeof
	$(lang_typeof_binout)

$(lang_typeof_binout): $(lang_root)typeof/to.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# union
lang_union_binout := $(bin_path)$(lang_prefix)_union$(bin_ext)

lang_union: $(lang_union_binout)
lang_union_test: lang_union
	$(lang_union_binout)

$(lang_union_binout): $(lang_root)union/u.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# volatile
volatile_basic_binout := $(bin_path)$(lang_prefix)_volatile_basic$(bin_ext)
volatile_pointer_binout := $(bin_path)$(lang_prefix)_volatile_pointer$(bin_ext)
volatile_struct_binout := $(bin_path)$(lang_prefix)_volatile_struct$(bin_ext)

lang_volatile: $(volatile_basic_binout)					\
               $(volatile_pointer_binout)				\
               $(volatile_struct_binout)
lang_volatile_test: lang_volatile_basic_test		\
                    lang_volatile_pointer_test	\
                    lang_volatile_struct_test

lang_volatile_basic_test: $(volatile_basic_binout)
	$(volatile_basic_binout)
lang_volatile_pointer_test: $(volatile_pointer_binout)
	$(volatile_pointer_binout)
lang_volatile_struct_test: $(volatile_struct_binout)
	$(volatile_struct_binout)

$(volatile_basic_binout): $(lang_root)volatile/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(volatile_pointer_binout): $(lang_root)volatile/pointer.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(volatile_struct_binout): $(lang_root)volatile/struct.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

