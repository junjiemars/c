#
# ./configure --has-lang
#
#


lang: lang_array                                \
      lang_assert                               \
      lang_duration                             \
      lang_enum                                 \
      lang_env                                  \
      lang_error                                \
      lang_exit                                 \
      lang_fn                                   \
      lang_goto                                 \
      lang_iso646                               \
      lang_jmp                                  \
      lang_linkage                              \
      lang_locale                               \
      lang_macro                                \
      lang_main                                 \
      lang_math                                 \
      lang_pointer                              \
      lang_preprocess                           \
      lang_random                               \
      lang_restrict                             \
      lang_scope                                \
      lang_signal                               \
      lang_sizeof                               \
      lang_stage                                \
      lang_storage                              \
      lang_string                               \
      lang_struct                               \
      lang_time                                 \
      lang_trigraphs                            \
      lang_type                                 \
      lang_typedef                              \
      lang_typeof                               \
      lang_union                                \
      lang_variadic                             \
      lang_volatile


lang_test:  lang_array_test                     \
            lang_assert_test                    \
            lang_duration_test                  \
            lang_enum_test                     \
            lang_env_test                      \
            lang_error_test                    \
            lang_exit_test                     \
            lang_fn_test                       \
            lang_goto_test                      \
            lang_iso646_test                    \
            lang_jmp_test                       \
            lang_linkage_test                   \
            lang_locale_test                    \
            lang_macro_test                     \
            lang_main_test                      \
            lang_math_test                      \
            lang_pointer_test                   \
            lang_preprocess_test                \
            lang_random_test                    \
            lang_restrict_test                  \
            lang_scope_test                     \
            lang_signal_test                    \
            lang_sizeof_test                    \
            lang_stage_test                     \
            lang_storage_test                   \
            lang_string_test                    \
            lang_struct_test                    \
            lang_time_test                      \
            lang_trigraphs_test                 \
            lang_type_test                      \
            lang_typedef_test                   \
            lang_typeof_test                    \
            lang_union_test                     \
            lang_variadic_test                  \
            lang_volatile_test

# env
lang_prefix := lang

INC += $(nm_inc_opt)$(root) $(nm_inc_opt)$(lang_root) $(nm_inc_opt)$(root)/posix


ifeq ($(_MEMORY_),1)
CFLAGS += $(f_sanitize)
endif # end of _MEMORY_



# array
lang_array_binout := $(bin_path)/$(lang_prefix)_lang_array$(bin_ext)

lang_array: $(lang_array_binout)
lang_array_test: lang_array
	$(lang_array_binout)

$(lang_array_binout): $(lang_root)/array/a1.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# assert
lang_assert_binout := $(bin_path)/$(lang_prefix)_assert$(bin_ext)
lang_assert_cppout := $(tmp_path)/$(lang_prefix)_assert$(cpp_ext)

lang_assert: $(lang_assert_binout)
lang_assert_test: lang_assert
	-$(lang_assert_binout) -1
	-$(lang_assert_binout) 101
	-$(lang_assert_binout) 49

$(lang_assert_binout): $(lang_assert_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_assert_cppout): $(lang_root)/assert/a.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# duration
lang_duration_binout := $(bin_path)/$(lang_prefix)_duration$(bin_ext)
lang_duration_extern_objout := $(bin_path)/$(lang_prefix)_duration_extern$(obj_ext)
lang_duration_d_objout := $(bin_path)/$(lang_prefix)_duration_d$(obj_ext)

lang_duration: $(lang_duration_binout)
lang_duration_test: lang_duration
	$(lang_duration_binout)

$(lang_duration_binout): $(lang_duration_extern_objout) \
                         $(lang_duration_d_objout)
	$(LINK) $(CFLAGS) $^ $(bin_out)$@

$(lang_duration_extern_objout): $(lang_root)/duration/extern.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(lang_duration_d_objout): $(lang_root)/duration/d.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# enum
lang_enum_binout := $(bin_path)/$(lang_prefix)_enum$(bin_ext)
lang_enum_cppout := $(tmp_path)/$(lang_prefix)_enum$(cpp_ext)

lang_enum: $(lang_enum_binout)
lang_enum_test: lang_enum
	$(lang_enum_binout)

$(lang_enum_binout): $(lang_enum_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_enum_cppout): $(lang_root)/enum/e.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# env
lang_env_lst_binout := $(bin_path)/$(lang_prefix)_env_lst$(bin_ext)
lang_env_get_binout := $(bin_path)/$(lang_prefix)_env_get$(bin_ext)
lang_env_set_binout := $(bin_path)/$(lang_prefix)_env_set$(bin_ext)
lang_env_set_cppout := $(tmp_path)/$(lang_prefix)_env_set$(cpp_ext)

lang_env: lang_env_lst                          \
          lang_env_get                          \
          lang_env_set

lang_env_test: lang_env_lst_test                \
               lang_env_get_test                \
               lang_env_set_test

lang_env_lst: $(lang_env_lst_binout)
lang_env_get: $(lang_env_get_binout)
lang_env_set: $(lang_env_set_binout)

lang_env_lst_test: lang_env_lst
	$(lang_env_lst_binout)

lang_env_get_test: lang_env_get
	$(lang_env_get_binout) --COUNT=2 --TEXT=Bonjour
	COUNT=2 $(lang_env_get_binout)
	COUNT=3 TEXT="Bonjor" $(lang_env_get_binout)
	COUNT=2 $(lang_env_get_binout) --TEXT=Bonjour

lang_env_set_test: lang_env_set
	$(lang_env_set_binout) "" "zzz"
	$(lang_env_set_binout) "XXX" "zzz"

$(lang_env_lst_binout): $(lang_root)/env/lst.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_env_get_binout): $(lang_root)/env/get.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_env_set_binout): $(lang_env_set_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_env_set_cppout): $(lang_root)/env/set.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# error
lang_error_basic_binout := $(bin_path)/$(lang_prefix)_error_basic$(bin_ext)

ifeq ($(NM_SYSTEM),Linux)
	error_ldlibs += $(nm_lib_opt)m
endif

lang_error: $(lang_error_basic_binout)
lang_error_test: lang_error
	$(lang_error_basic_binout) $(CURDIR)/Makefilex
	$(lang_error_basic_binout) $(CURDIR)/Makefile

$(lang_error_basic_binout): $(lang_root)/error/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(error_ldlibs)

# exit
lang_exit_binout := $(bin_path)/$(lang_prefix)_exit$(bin_ext)
lang__exit_binout := $(bin_path)/$(lang_prefix)__exit$(bin_ext)

lang_exit: $(lang_exit_binout)                  \
           $(lang__exit_binout)
lang_exit_test: lang_exit
	$(lang_exit_binout)
	$(lang__exit_binout)

$(lang_exit_binout): $(lang_root)/exit/e.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang__exit_binout): $(lang_root)/exit/e1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# fn
lang_fn_binout := $(bin_path)/$(lang_prefix)_fn$(bin_ext)

lang_fn: $(lang_fn_binout)
lang_fn_test: lang_fn
	$(lang_fn_binout)

$(lang_fn_binout): $(lang_root)/fn/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# goto
lang_goto_binout := $(bin_path)/$(lang_prefix)_goto$(bin_ext)

lang_goto: $(lang_goto_binout)
lang_goto_test: lang_goto
	$(lang_goto_binout)

$(lang_goto_binout): $(lang_root)/goto/g.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# iso646
lang_iso646_binout := $(bin_path)/$(lang_prefix)_iso646$(bin_ext)

lang_iso646: $(lang_iso646_binout)
lang_iso646_test: lang_iso646
	$(lang_iso646_binout) iso646

$(lang_iso646_binout): $(lang_root)/iso646/646.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# jmp
lang_jmp_basic_binout := $(bin_path)/$(lang_prefix)_jmp_basic$(bin_ext)
lang_jmp_var_binout := $(bin_path)/$(lang_prefix)_jmp_var$(bin_ext)
lang_jmp_catch_binout := $(bin_path)/$(lang_prefix)_jmp_catch$(bin_ext)
lang_jmp_catch_cppout := $(tmp_path)/$(lang_prefix)_jmp_catch$(cpp_ext)

lang_jmp: lang_jmp_basic                        \
          lang_jmp_var                          \
          lang_jmp_catch
lang_jmp_test: lang_jmp_basic_test              \
               lang_jmp_var_test                \
               lang_jmp_catch_test

lang_jmp_basic: $(lang_jmp_basic_binout)
lang_jmp_basic_test: lang_jmp_basic
	$(lang_jmp_basic_binout)

lang_jmp_var: $(lang_jmp_var_binout)
lang_jmp_var_test: lang_jmp_var
	$(lang_jmp_var_binout)

lang_jmp_catch: $(lang_jmp_catch_binout)
lang_jmp_catch_test: lang_jmp_catch
	$(lang_jmp_catch_binout)

$(lang_jmp_basic_binout): $(lang_root)/jmp/j.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_jmp_var_binout): $(lang_root)/jmp/v.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_jmp_catch_binout): $(lang_jmp_catch_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_jmp_catch_cppout): $(lang_root)/jmp/catch.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# linkage
lang_linkage_lnkc_binout := $(bin_path)/$(lang_prefix)_linkage_lnkc$(bin_ext)
lang_linkage_lnk_objout := $(tmp_path)/$(lang_prefix)_linkage_lnk$(obj_ext)
lang_linkage_c_objout := $(tmp_path)/$(lang_prefix)_linkage_c$(obj_ext)
lang_linkage_whole_binout := $(bin_path)/$(lang_prefix)_linkage_whole$(bin_ext)

ifeq ($(NM_SYSTEM), WinNT)
lang_linkage:
	@echo "skip ..."
lang_linkage_test: lang_linkage
else
# has_sanitize conflict
lang_linkage: $(lang_linkage_lnkc_binout)       \
              $(lang_linkage_whole_binout)
lang_linkage_test: lang_linkage_lnkc_test       \
                   lang_linkage_whole_test
endif

lang_linkage_lnkc_test: $(lang_linkage_lnkc_binout)
	$(lang_linkage_lnkc_binout)
lang_linkage_whole_test: $(lang_linkage_whole_binout)
	$(lang_linkage_whole_binout)

$(lang_linkage_lnkc_binout): $(lang_linkage_lnk_objout) \
                             $(lang_linkage_c_objout)
	$(LINK) $^ $(bin_out)$@

$(lang_linkage_whole_binout): $(lang_root)/linkage/c.c    \
                              $(lang_root)/linkage/lnk.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_linkage_lnk_objout): $(lang_root)/linkage/lnk.c  \
                            $(lang_root)/linkage/lnk.h
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $< $(obj_out)$@

$(lang_linkage_c_objout): $(lang_root)/linkage/c.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# locale
lang_locale_binout := $(bin_path)/$(lang_prefix)_locale$(bin_ext)

lang_locale: $(lang_locale_binout)
lang_locale_test: lang_locale
	$(lang_locale_binout)
	$(lang_locale_binout) "C"
	$(lang_locale_binout) "POSIX"
	$(lang_locale_binout) "en_US"
	$(lang_locale_binout) "fr_FR"
	$(lang_locale_binout) "zh_CN"
	$(lang_locale_binout) "zh_HK"
	$(lang_locale_binout) "XXX"

$(lang_locale_binout): $(lang_root)/locale/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# macro
lang_macro_binout := $(bin_path)/$(lang_prefix)_macro$(bin_ext)
lang_macro_cppout := $(tmp_path)/$(lang_prefix)_macro$(cpp_ext)

lang_macro: $(lang_macro_binout)
lang_macro_test: lang_macro
	$(lang_macro_binout)

$(lang_macro_binout): $(lang_macro_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_macro_cppout): $(lang_root)/macro/macro.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@



# main
lang_main_raw_binout := $(bin_path)/$(lang_prefix)_main_raw$(bin_ext)
lang_main_envp_binout := $(bin_path)/$(lang_prefix)_main_envp$(bin_ext)

lang_main: $(lang_main_raw_binout)              \
           $(lang_main_envp_binout)
lang_main_test: lang_main_raw_test              \
                lang_main_envp_test
lang_main_raw_test: $(lang_main_raw_binout)
	$< a bb ccc
lang_main_envp_test: $(lang_main_envp_binout)
	ZZZ=xyz $<

$(lang_main_raw_binout): $(lang_root)/main/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_main_envp_binout): $(lang_root)/main/m_envp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# math
lang_math_complex_binout := $(bin_path)/$(lang_prefix)_math_complex$(bin_ext)
lang_math_float_binout := $(bin_path)/$(lang_prefix)_math_float$(bin_ext)
lang_math_float_cppout := $(tmp_path)/$(lang_prefix)_math_float$(cpp_ext)

lang_math: $(lang_math_complex_binout)          \
           $(lang_math_float_binout)
lang_math_test: lang_math_complex_test          \
                lang_math_float_test

lang_math_complex_test: $(lang_math_complex_binout)
	$(lang_math_complex_binout)

lang_math_float_test: $(lang_math_float_binout)
	$(lang_math_float_binout)

$(lang_math_complex_binout): $(lang_root)/math/m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_math_float_binout): $(lang_math_float_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_math_float_cppout): $(lang_root)/math/f.c
	$(CPP) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# random
lang_random_basic_binout := $(bin_path)/$(lang_prefix)_random_raw$(bin_ext)
# lang_random_arc_binout := $(bin_path)/$(lang_prefix)_random_arc$(bin_ext)
lang_random_secure_binout := $(bin_path)/$(lang_prefix)_random_secure$(bin_ext)
lang_random_seed_binout := $(bin_path)/$(lang_prefix)_random_seed$(bin_ext)

lang_random: lang_random_basic                  \
             lang_random_secure                 \
             lang_random_seed
lang_random_test: lang_random_basic_test        \
                  lang_random_secure_test       \
                  lang_random_seed_test

lang_random_basic: $(lang_random_basic_binout)
lang_random_basic_test: lang_random_basic
	$(lang_random_basic_binout) 10
	$(lang_random_basic_binout) 10 -10 10

# lang_random_arc: $(lang_random_arc_binout)
# lang_random_arc_test: lang_random_arc
# 	$(lang_random_arc_binout)
# 	$(lang_random_arc_binout) 20

lang_random_secure: $(lang_random_secure_binout)
lang_random_secure_test: lang_random_secure
	$(lang_random_secure_binout) 10

lang_random_seed: $(lang_random_seed_binout)
lang_random_seed_test: lang_random_seed
	$(lang_random_seed_binout) 1 10
	$(lang_random_seed_binout) 1 10
	$(lang_random_seed_binout) 2 10

$(lang_random_basic_binout): $(lang_root)/random/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_random_arc_binout): $(lang_root)/random/arc.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_random_secure_binout): $(lang_root)/random/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_random_seed_binout): $(lang_root)/random/seed.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# restrict
lang_restrict_binout := $(bin_path)/$(lang_prefix)_restrict$(bin_ext)

lang_restrict: $(lang_restrict_binout)
lang_restrict_test: lang_restrict
	$(lang_restrict_binout)

$(lang_restrict_binout): $(lang_root)/restrict/r1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# pointer
lang_ptr_basic_binout := $(bin_path)/$(lang_prefix)_ptr_basic$(bin_ext)
lang_ptr_const_binout := $(bin_path)/$(lang_prefix)_ptr_const$(bin_ext)
lang_ptr_fn_binout := $(bin_path)/$(lang_prefix)_ptr_fn$(bin_ext)
lang_ptr_size_binout := $(bin_path)/$(lang_prefix)_ptr_size$(bin_ext)
lang_ptr_void_binout := $(bin_path)/$(lang_prefix)_ptr_void$(bin_ext)
lang_ptr_lvalue_binout := $(bin_path)/$(lang_prefix)_ptr_lvalue$(bin_ext)
lang_ptr_arith_binout := $(bin_path)/$(lang_prefix)_ptr_arith$(bin_ext)

lang_pointer: lang_ptr_basic                    \
              lang_ptr_const                    \
              lang_ptr_fn                       \
              lang_ptr_size                     \
              lang_ptr_void                     \
              lang_ptr_lvalue                   \
              lang_ptr_arith

lang_pointer_test: lang_ptr_basic_test          \
                   lang_ptr_const_test          \
                   lang_ptr_fn_test             \
                   lang_ptr_size_test           \
                   lang_ptr_void_test           \
                   lang_ptr_lvalue              \
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

$(lang_ptr_basic_binout): $(lang_root)/pointer/basic.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_const_binout): $(lang_root)/pointer/const.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_fn_binout): $(lang_root)/pointer/fn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_size_binout): $(lang_root)/pointer/size.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_void_binout): $(lang_root)/pointer/void.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_lvalue_binout): $(lang_root)/pointer/lvalue.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_ptr_arith_binout): $(lang_root)/pointer/arith.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# preprocess
lang_preprocess_binout := $(bin_path)/$(lang_prefix)_preprocess$(bin_ext)
lang_preprocess_cppout := $(tmp_path)/$(lang_prefix)_preprocess$(cpp_ext)
lang_preprocess_flags =
ifneq ($(_ERROR_),)
lang_preprocess_flags += -D_ERROR_=$(_ERROR_)
endif
ifneq ($(_WARNING_),)
lang_preprocess_flags += -D_WARNING_=$(_WARNING_)
endif

lang_preprocess: $(lang_preprocess_binout)
lang_preprocess_test: lang_preprocess
	$(lang_preprocess_binout)

$(lang_preprocess_binout): $(lang_preprocess_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_preprocess_cppout): $(lang_root)/preprocess/p.c
	$(CPP) $(CPPFLAGS) $(INC) ${lang_preprocess_flags} $(nm_stage_pre) $^ $(cpp_out)$@

# scope
lang_scope_binout := $(bin_path)/$(lang_prefix)_scope$(bin_ext)
lang_scope_cppout := $(tmp_path)/$(lang_prefix)_scope$(cpp_ext)

scope_cflags = $(CFLAGS)
ifeq ($(CC_NAME), msvc)
	scope_cflags += -Wv:18
endif

lang_scope: $(lang_scope_binout)
lang_scope_test: lang_scope
	$(lang_scope_binout)

$(lang_scope_binout): $(lang_scope_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_scope_cppout): $(lang_root)/scope/scope.c
	$(CPP) $(CPPFLAGS) $(INC) $^ $(nm_stage_pre) $(cpp_out)$@


# signal
lang_signal_basic_binout := $(bin_path)/$(lang_prefix)_signal_basic$(bin_ext)

lang_signal: lang_signal_basic
lang_signal_test: lang_signal_basic_test

lang_signal_basic: $(lang_signal_basic_binout)
lang_signal_basic_test: lang_signal_basic
	$(lang_signal_basic_binout)

$(lang_signal_basic_binout): $(lang_root)/signal/sig.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# sizeof
lang_sizeof_binout := $(bin_path)/$(lang_prefix)_sizeof$(bin_ext)

lang_sizeof: $(lang_sizeof_binout)
lang_sizeof_test: lang_sizeof
	$(lang_sizeof_binout)

$(lang_sizeof_binout): $(lang_root)/sizeof/s1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# stage
stage_binout := $(bin_path)/$(lang_prefix)_stage$(bin_ext)
stage_objout := $(tmp_path)/$(lang_prefix)_stage$(obj_ext)
stage_asmout := $(tmp_path)/$(lang_prefix)_stage$(asm_ext)
stage_cppout := $(tmp_path)/$(lang_prefix)_stage$(cpp_ext)

ifeq ($(CC_NAME),msvc)
lang_stage:
	@echo "#skip lang_stage_test"
lang_stage_test: lang_stage
stage_ldflags := -link -FORCE:MULTIPLE
ifeq ($(NM_VERBOSE),YES)
stage_ldflags += -VERBOSE:LIB
endif # end of NM_VERBOSE
else
lang_stage: $(stage_binout)
lang_stage_test: lang_stage
	$(stage_binout)
endif # end of CC_NAME

$(stage_binout): $(stage_objout)
	$(LINK) $^ $(bin_out)$@ $(stage_ldflags)

$(stage_objout): $(stage_asmout)
	$(CC) $(CFLAGS) $(nm_stage_c) $^ $(obj_out)$@

$(stage_asmout): $(stage_cppout)
	$(ASM) $(ASFLAGS) $(nm_stage_asm) $^ $(asm_out)$@

$(stage_cppout): $(lang_root)/stage/s.c
	$(CPP) $(CPPFLAGS) $(nm_stage_pre) $(INC) $^ $(cpp_out)$@


# storage
lang_stor_binout := $(bin_path)/$(lang_prefix)_storage$(bin_ext)
lang_stor_extern_objout := $(tmp_path)/$(lang_prefix)_storage_extern$(obj_ext)
lang_stor_s_objout := $(tmp_path)/$(lang_prefix)_storage_s$(obj_ext)

lang_storage: $(lang_stor_binout)
lang_storage_test: lang_storage
	$(lang_stor_binout)

$(lang_stor_binout): $(lang_stor_extern_objout) $(lang_stor_s_objout)
	$(LINK) $^ $(bin_out)$@

$(lang_stor_s_objout): $(lang_root)/storage/s.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

$(lang_stor_extern_objout): $(lang_root)/storage/extern.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(obj_out)$@

# string
lang_string_basic_binout := $(bin_path)/$(lang_prefix)_string_basic$(bin_ext)
lang_string_n_binout := $(bin_path)/$(lang_prefix)_string_n$(bin_ext)
lang_string_s_binout := $(bin_path)/$(lang_prefix)_string_s$(bin_ext)
lang_string_dup_binout := $(bin_path)/$(lang_prefix)_string_dup$(bin_ext)
lang_string_tok_binout := $(bin_path)/$(lang_prefix)_string_tok$(bin_ext)
lang_string_cat_binout := $(bin_path)/$(lang_prefix)_string_cat$(bin_ext)
lang_string_chr_binout := $(bin_path)/$(lang_prefix)_string_chr$(bin_ext)
lang_string_pbrk_binout := $(bin_path)/$(lang_prefix)_string_pbrk$(bin_ext)
lang_string_spn_binout := $(bin_path)/$(lang_prefix)_string_spn$(bin_ext)

lang_string: lang_string_basic                  \
             lang_string_n                      \
             lang_string_s                      \
             lang_string_dup                    \
             lang_string_tok                    \
             lang_string_cat                    \
             lang_string_chr                    \
             lang_string_pbrk                   \
             lang_string_spn

lang_string_test: lang_string_basic_test        \
                  lang_string_n_test            \
                  lang_string_s_test            \
                  lang_string_dup_test          \
                  lang_string_tok_test          \
                  lang_string_cat_test          \
                  lang_string_chr_test          \
                  lang_string_pbrk_test         \
                  lang_string_spn_test

lang_string_basic: $(lang_string_basic_binout)
lang_string_basic_test: lang_string_basic
	$(lang_string_basic_binout)

lang_string_n: $(lang_string_n_binout)
lang_string_n_test: lang_string_n
	$(lang_string_n_binout) "abcd12345678" "abcd"
	$(lang_string_n_binout) "abcd" "abcd12345678"

lang_string_s: $(lang_string_s_binout)
lang_string_s_test: lang_string_s
	$(lang_string_s_binout)

lang_string_dup: $(lang_string_dup_binout)
lang_string_dup_test: lang_string_dup
	$(lang_string_dup_binout) "the quick brown fox"

lang_string_tok: $(lang_string_tok_binout)
lang_string_tok_test: lang_string_tok
	$(lang_string_tok_binout) "this is a simple sample for strtok." " ."
	$(lang_string_tok_binout) "this is a simple    sample for strtok." " ."

lang_string_cat: $(lang_string_cat_binout)
lang_string_cat_test: lang_string_cat
	$(lang_string_cat_binout) "the quick brown fox" " jumps over the lazy dog"
	$(lang_string_cat_binout) "the quick brown fo" ""
	$(lang_string_cat_binout) "" "umps over the lazy dog"

lang_string_chr: $(lang_string_chr_binout)
lang_string_chr_test: lang_string_chr
	$(lang_string_chr_binout) "the quick brown fox jumps over the lazy dog" "j"
	$(lang_string_chr_binout) "the quick brown fox jumps over the lazy dog" "t"
	$(lang_string_chr_binout) "the quick brown fox jumps over the lazy dog" "1"

lang_string_pbrk: $(lang_string_pbrk_binout)
lang_string_pbrk_test: lang_string_pbrk
	$(lang_string_pbrk_binout) "the quick brown fox jumps over the lazy dog" "fxx"
	$(lang_string_pbrk_binout) "the quick brown fox jumps over the lazy dog" "dxx"
	$(lang_string_pbrk_binout) "the quick brown fox jumps over the lazy dog" "123"

lang_string_spn: $(lang_string_spn_binout)
lang_string_spn_test: lang_string_spn
	$(lang_string_spn_binout) "the quick brown fox jumps over the lazy dog" "f"
	$(lang_string_spn_binout) "the quick brown fox jumps over the lazy dog" "q"
	$(lang_string_spn_binout) "the quick brown fox jumps over the lazy dog" "the q"
	$(lang_string_spn_binout) "the quick brown fox jumps over the lazy dog" "fthe q"
	$(lang_string_spn_binout) "the quick brown fox jumps over the lazy dog" "fthe x"

$(lang_string_basic_binout): $(lang_root)/string/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_n_binout): $(lang_root)/string/n.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_s_binout): $(lang_root)/string/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_dup_binout): $(lang_root)/string/dup.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_tok_binout): $(lang_root)/string/tok.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_cat_binout): $(lang_root)/string/cat.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_chr_binout): $(lang_root)/string/chr.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_pbrk_binout): $(lang_root)/string/pbrk.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_string_spn_binout): $(lang_root)/string/spn.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# struct
lang_struct_binout := $(bin_path)/$(lang_prefix)_struct$(bin_ext)

lang_struct: $(lang_struct_binout)
lang_struct_test: lang_struct
	$(lang_struct_binout)

$(lang_struct_binout): $(lang_root)/struct/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# time
lang_time_basic_binout := $(bin_path)/$(lang_prefix)_time_basic$(bin_ext)
lang_time_clock_binout := $(bin_path)/$(lang_prefix)_time_clock$(bin_ext)
lang_time_conv_binout := $(bin_path)/$(lang_prefix)_time_conv$(bin_ext)

lang_time: $(lang_time_basic_binout)            \
           $(lang_time_clock_binout)            \
           $(lang_time_conv_binout)
lang_time_test: lang_time_basic_test            \
                lang_time_clock_test            \
                lang_time_conv_test

lang_time_basic_test: $(lang_time_basic_binout)
	$(lang_time_basic_binout)
lang_time_clock_test: $(lang_time_clock_binout)
	$(lang_time_clock_binout) 64
lang_time_conv_test: $(lang_time_conv_binout)
	$(lang_time_conv_binout)
	$(lang_time_conv_binout) 1594560256

lang_time_conv_test: $(lang_time_conv_binout)

$(lang_time_basic_binout): $(lang_root)/time/bt.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_time_clock_binout): $(lang_root)/time/c.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(lang_time_conv_binout): $(lang_root)/time/conv.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# trigraphs
lang_trigraphs_binout := $(bin_path)/$(lang_prefix)_trigraphs$(bin_ext)

lang_trigraphs: $(lang_trigraphs_binout)
lang_trigraphs_test: lang_trigraphs
	$(lang_trigraphs_binout) trigraphs

$(lang_trigraphs_binout): $(lang_root)/trigraphs/tri.c
	$(CC) $(CFLAGS) $(nm_trigraphs_opt) $(INC) $^ $(bin_out)$@



# type
lang_type_int_binout := $(bin_path)/$(lang_prefix)_type_int$(bin_ext)
lang_type_int_cppout := $(tmp_path)/$(lang_prefix)_type_int$(cpp_ext)
lang_type_c_binout := $(bin_path)/$(lang_prefix)_type_c$(bin_ext)
lang_type_c_cppout := $(tmp_path)/$(lang_prefix)_type_c$(cpp_ext)
lang_type_float_binout := $(bin_path)/$(lang_prefix)_type_float$(bin_ext)
lang_type_size_binout := $(bin_path)/$(lang_prefix)_size$(bin_ext)

lang_type: $(lang_type_int_binout)              \
           $(lang_type_c_binout)                \
           $(lang_type_size_binout)
lang_type_test: lang_type_int_test              \
                lang_type_c_test                \
                lang_type_float_test            \
                lang_type_size_test

lang_type_int_test: $(lang_type_int_binout)
	$(lang_type_int_binout)
lang_type_c_test: $(lang_type_c_binout)
	$(lang_type_c_binout) 11ff22aa
lang_type_float_test: $(lang_type_float_binout)
	$<
lang_type_size_test: $(lang_type_size_binout)
	$<

$(lang_type_int_binout): $(lang_type_int_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_type_int_cppout): $(lang_root)/type/int.c
	$(CPP) $(INC) $(CPPFLAGS) $(nm_stage_pre) $^ $(cpp_out)$@

$(lang_type_c_binout): $(lang_type_c_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_type_c_cppout): $(lang_root)/type/ct.c
	$(CPP) $(INC) $(CPPFLAGS) $(nm_stage_pre) $^ $(cpp_out)$@

$(lang_type_float_binout): $(lang_root)/type/float.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


$(lang_type_size_binout): $(lang_root)/type/sz.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@



# typedef
lang_typedef_binout := $(bin_path)/$(lang_prefix)_typedef$(bin_ext)

lang_typedef: $(lang_typedef_binout)
lang_typedef_test: lang_typedef
	$(lang_typedef_binout)

$(lang_typedef_binout): $(lang_root)/typedef/t.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# typeof
lang_typeof_binout := $(bin_path)/$(lang_prefix)_typeof$(bin_ext)

lang_typeof: $(lang_typeof_binout)
lang_typeof_test: lang_typeof
	$(lang_typeof_binout)

$(lang_typeof_binout): $(lang_root)/typeof/to.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# union
lang_union_binout := $(bin_path)/$(lang_prefix)_union$(bin_ext)

lang_union: $(lang_union_binout)
lang_union_test: lang_union
	$(lang_union_binout)

$(lang_union_binout): $(lang_root)/union/u.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# variadic
lang_variadic_binout := $(bin_path)/$(lang_prefix)_variadic$(bin_ext)
lang_variadic_cppout := $(tmp_path)/$(lang_prefix)_variadic$(cpp_ext)

lang_variadic: $(lang_variadic_binout)
lang_variadic_test: lang_variadic
	$(lang_variadic_binout)

$(lang_variadic_binout): $(lang_variadic_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(lang_variadic_cppout): $(lang_root)/variadic/v.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@



# volatile
volatile_basic_binout := $(bin_path)/$(lang_prefix)_volatile_basic$(bin_ext)
volatile_pointer_binout := $(bin_path)/$(lang_prefix)_volatile_pointer$(bin_ext)
volatile_struct_binout := $(bin_path)/$(lang_prefix)_volatile_struct$(bin_ext)

lang_volatile: $(volatile_basic_binout)         \
               $(volatile_pointer_binout)       \
               $(volatile_struct_binout)
lang_volatile_test: lang_volatile_basic_test    \
                    lang_volatile_pointer_test  \
                    lang_volatile_struct_test

lang_volatile_basic_test: $(volatile_basic_binout)
	$(volatile_basic_binout)
lang_volatile_pointer_test: $(volatile_pointer_binout)
	$(volatile_pointer_binout)
lang_volatile_struct_test: $(volatile_struct_binout)
	$(volatile_struct_binout)

$(volatile_basic_binout): $(lang_root)/volatile/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(volatile_pointer_binout): $(lang_root)/volatile/pointer.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(volatile_struct_binout): $(lang_root)/volatile/struct.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@



# eof
