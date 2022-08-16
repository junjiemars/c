#
# ./configure --has-zig
# make clean test
#


zig: zig_hi
zig_test: zig_hi_test


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




