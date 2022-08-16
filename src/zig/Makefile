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
zig_c_zigout := $(zig_root)/c/zig-out/bin/z1


zig_c: $(zig_c_binout)
zig_c_test: zig_c_binout_test                   \
            zig_c_zigout_test

zig_c_binout_test: $(zig_c_binout)
	$<

zig_c_zigout_test: $(zig_c_zigout)
	$<

$(zig_c_binout): $(zig_root)/c/c.c              \
                 $(zig_root)/c/m.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


$(zig_c_zigout): $(zig_root)/c/build.zig        \
                 $(zig_root)/c/c.c              \
                 $(zig_root)/c/m.c
	cd $(zig_root)/c && $(ZIG) build


