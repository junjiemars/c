#
# ./configure --without-debug --has-ld
#

ld: ld_nostdlib

ld_test: ld_nostdlib_test

ld_prefix := ld
INC += -I$(ld_root)

CFLAGS += -nostdlib

# nostdlib
ld_nostdlib_binout := $(bin_path)/$(ld_prefix)_nostdlib$(bin_ext)

ld_nostdlib: $(ld_nostdlib_binout)
ld_nostdlib_test: ld_nostdlib
	$(ld_nostdlib_binout)

$(ld_nostdlib_binout): $(ld_root)/nostdlib/n.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# eof
