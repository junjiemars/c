
source_path := $(src_path)examples_unix/source
include_path := $(src_path)examples_unix/include
examples_path := $(src_path)examples_unix/examples

INC += -I$(include_path)

mac: bit \
		 bitree \
		 bistree
mac_test: bit_test \
				  bistree_test 

bit_binout := $(bin_path)bit$(bin_ext)
bit: $(bit_binout)
bit_test: bit
	$(bit_binout)
$(bit_binout): $(source_path)/bit.c $(examples_path)/bit/ex-1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

bitree_libout := $(lib_path)libbitree$(mod_ext)
bitree: $(bitree_libout)
$(bitree_libout): $(source_path)/bitree.c
	$(CC) $(LFLAGS) $(LDFLAGS) $(INC) $^ $(bin_out)$@

bistree_binout := $(bin_path)bistree$(bin_ext)
bitree_objout := $(obj_path)bitree$(obj_ext)
bistree: bitree $(bistree_binout)
bistree_test: bistree
	$(bistree_binout)
$(bistree_binout): $(source_path)/bistree.c $(examples_path)/bistree/ex-1.c
	$(CC) $(CFLAGS) $(INC) $(LDLIBS) $^ -lbitree $(bin_out)$@
