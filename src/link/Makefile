#
# ./configure --has-link
#

link_prefix := link
INC += -I$(root) -I$(link_root) -I$(root)/posix


link: link_nm

link_test:  link_nm_test

INC += -I/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include
CFLAGS += -v
LDFLAGS += -L/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/lib
LDLIBS += -lxcselect

# nm
link_nm_binout := $(bin_path)/$(link_prefix)_nm$(bin_ext)

link_nm: $(link_nm_binout)
link_nm_test: link_nm
	$(link_nm_binout)

$(link_nm_binout): $(link_root)/nm/n.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDFLAGS) $(LDLIBS)


.PHONY: link_nm link_nm_test

# eof
