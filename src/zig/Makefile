#
# ./configure --has-zig
# make clean test
#


zig: zig_hi                                     \
     zig_c                                      \
     zig_game
zig_test: zig_hi_test                           \
          zig_c_test                            \
          zig_game_test


# env
ZIG := $(shell which zig)
zig_prefix := zig
zig_cache_dir := $(CURDIR)/$(tmp_path)/zig-cache
zig_prefix_exe_dir := $(CURDIR)/$(bin_path)

zig_clean: $(bin_path)
	-$(RM) -r $(bin_path)/*


# hi
zig_hi_build := $(CURDIR)/$(zig_root)/hi/build.zig
zig_hi_binout := $(bin_path)/hi$(bin_ext)


zig_hi: $(zig_hi_binout)
zig_hi_test: zig_hi
	$(zig_hi_binout)

$(zig_hi_build): $(ZIG)
	cd $(zig_root)/hi && $(ZIG) init-exe

$(zig_hi_binout): $(zig_hi_build)
	$(ZIG) build                                  \
    --build-file $<                             \
    --cache-dir $(zig_cache_dir)                \
    --prefix-exe-dir $(zig_prefix_exe_dir)      \
    -Drelease-small=true

# c
zig_c_binout := $(bin_path)/$(zig_prefix)_c$(bin_ext)
zig_c_zig_binout := $(bin_path)/$(zig_prefix)_z0$(bin_ext)
zig_c_zigout1 := $(bin_path)/$(zig_prefix)_z1$(bin_ext)
zig_c_zigout2 := $(bin_path)/$(zig_prefix)_z2$(bin_ext)
zig_c_zigout3 := $(bin_path)/$(zig_prefix)_z3$(bin_ext)
zig_c_root := $(CURDIR)/$(zig_root)/c

zig_c: $(zig_c_binout)                          \
       $(zig_c_zig_binout)                      \
       $(zig_c_zigout1)                         \
       $(zig_c_zigout2)
zig_c_test: zig_c_binout_test                   \
            zig_c_zig_binout_test               \
            zig_c_zigout1_test                  \
            zig_c_zigout2_test                  \
            zig_c_zigout3_test

zig_c_binout_test: $(zig_c_binout)
	$<
zig_c_zig_binout_test: $(zig_c_zig_binout)
	$<
zig_c_zigout1_test: $(zig_c_zigout1)
	$<
zig_c_zigout2_test: $(zig_c_zigout2)
	$<
zig_c_zigout3_test: $(zig_c_zigout3)
	$<

$(zig_c_binout): $(zig_root)/c/c.c              \
                 $(zig_root)/c/m.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(zig_c_zig_binout): $(zig_root)/c/c.c          \
                     $(zig_root)/c/m.c
	$(ZIG) cc $(CPPFLAGS) $(CFLAGS) $(INC) $^ -o $@


$(zig_c_zigout1): $(zig_root)/c/build1.zig      \
                  $(zig_root)/c/c.c             \
                  $(zig_root)/c/m.c
	$(ZIG) build                                  \
    --build-file $(zig_c_root)/build1.zig       \
    --cache-dir $(zig_cache_dir)                \
    --prefix-exe-dir $(zig_prefix_exe_dir)

$(zig_c_zigout2): $(zig_root)/c/build2.zig      \
                  $(zig_root)/c/c.c             \
                  $(zig_root)/c/m.zig
	$(ZIG) build                                  \
    --build-file $(zig_c_root)/build2.zig       \
    --cache-dir $(zig_cache_dir)                \
    --prefix-exe-dir $(zig_prefix_exe_dir)

$(zig_c_zigout3): $(zig_root)/c/build3.zig      \
                  $(zig_root)/c/c.zig           \
                  $(zig_root)/c/m.c
	$(ZIG) build                                  \
    --build-file $(zig_c_root)/build3.zig       \
    --cache-dir $(zig_cache_dir)                \
    --prefix-exe-dir $(zig_prefix_exe_dir)


# game
zig_game_build := $(CURDIR)/$(zig_root)/game/build.zig
zig_game_binout := $(bin_path)/$(zig_prefix)_game$(bin_ext)

zig_game: $(zig_game_binout)
zig_game_test: zig_game
	echo 39 | $(zig_game_binout)

$(zig_game_build): $(ZIG)
	cd $(zig_root)/game && $(ZIG) init-exe

$(zig_game_binout): $(zig_game_build)             \
                    $(zig_root)/game/src/main.zig
	$(ZIG) build                                  \
    --build-file $<                             \
    --cache-dir $(zig_cache_dir)                \
    --prefix-exe-dir $(zig_prefix_exe_dir)
