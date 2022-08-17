#
# ./configure --has-zig
# make clean test
#


zig: zig_hi                                     \
     zig_c
zig_test: zig_hi_test                           \
          zig_c_test


# env
zig_prefix := zig
ZIG := $(shell which zig)

# hi
zig_hi_build := $(zig_root)/hi/build.zig

zig_hi: $(zig_hi_build)
zig_hi_test: zig_hi
	cd $(zig_root)/hi && $(ZIG) build run

$(zig_hi_build): $(ZIG)
	cd $(zig_root)/hi && $(ZIG) init-exe

# c
zig_c_binout := $(bin_path)/$(zig_prefix)_c$(bin_ext)
zig_c_zig_binout := $(bin_path)/$(zig_prefix)_z0$(bin_ext)
zig_c_zigout1 := $(zig_root)/c/zig-out/bin/z1
zig_c_zigout2 := $(zig_root)/c/zig-out/bin/z2


zig_c: $(zig_c_binout)                          \
       $(zig_c_zig_binout)                      \
       $(zig_c_zigout1)                         \
       $(zig_c_zigout2)
zig_c_test: zig_c_binout_test                   \
            zig_c_zig_binout_test               \
            zig_c_zigout1_test                  \
            zig_c_zigout2_test

zig_c_binout_test: $(zig_c_binout)
	$<
zig_c_zig_binout_test: $(zig_c_zig_binout)
	$<
zig_c_zigout1_test: $(zig_c_zigout1)
	$<
zig_c_zigout2_test: $(zig_c_zigout2)
	$<

$(zig_c_binout): $(zig_root)/c/c.c              \
                 $(zig_root)/c/m.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(zig_c_zig_binout): $(zig_root)/c/c.c          \
                     $(zig_root)/c/m.c
	$(ZIG) cc $(CPPFLAGS) $(CFLAGS) $(INC) $^ -o $@ 


$(zig_c_zigout1): $(zig_root)/c/build1.zig       \
                  $(zig_root)/c/c.c             \
                  $(zig_root)/c/m.c
	cd $(zig_root)/c && $(ZIG) build \
		--build-file $(CURDIR)/$(zig_root)/c/build1.zig

$(zig_c_zigout2): $(zig_root)/c/build2.zig      \
                  $(zig_root)/c/c.c             \
                  $(zig_root)/c/m.zig
	cd $(zig_root)/c && $(ZIG) build                  \
		--build-file $(CURDIR)/$(zig_root)/c/build2.zig


