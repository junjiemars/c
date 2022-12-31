#
# ./configure --has-mix
#


ifeq ($(has_mix),no)
mix:
	@echo "#skip ..."
mix_test:
	@echo "#skip ..."
else


mix: mix_bone
mix_test: mix_bone_test

endif														# mix


# env
mix_prefix := mix
INC += $(nm_inc_opt)$(mix_root) $(nm_inc_opt)$(root)/posix


# bone
mix_bone_hi_binout := $(bin_path)/$(mix_prefix)_bone_hi$(bin_ext)

mix_bone: $(mix_bone_hi_binout)
mix_bone_test: mix_bone_hi_test

mix_bone_hi_test: $(mix_bone_hi_binout)
	$(mixvm) --run $<


$(mix_bone_hi_binout): $(mix_root)/bone/b1.mixal
	$(mixasm) -o$@ $^


# eof
