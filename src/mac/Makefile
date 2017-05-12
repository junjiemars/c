
source_path := $(src_path)examples_unix/source
include_path := $(src_path)examples_unix/include
examples_path := $(src_path)examples_unix/examples

INC += -I$(include_path)

mac: bit \
		 bitree \
		 bistree \
		 list \
		 set1 \
		 set2 

mac_test: bit_test \
				  bistree_test \
					list_test \
					set1_test \
					set2_test

#----------
# bit 
#----------
bit_binout := $(bin_path)bit$(bin_ext)
bit: $(bit_binout)
bit_test: bit
	$(bit_binout)
$(bit_binout): $(source_path)/bit.c $(examples_path)/bit/ex-1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

#----------
# bitree
#----------
bitree_libout := $(lib_path)libbitree$(lib_ext)
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

#----------
# list 
#----------

list_binout := $(bin_path)list$(bin_ext)
list: $(list_binout)
list_test: list
	$(list_binout)

$(list_binout): $(source_path)/list.c $(examples_path)/list/ex-1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

#----------
# set
#----------
set1_binout := $(bin_path)set1$(bin_ext)
set1: $(set1_binout)
set1_test: set1
	$(set1_binout)
$(set1_binout): $(source_path)/list.c \
                $(source_path)/set.c \
                $(examples_path)/set/ex-1.c
	$(CC) $(CFLAGS) $(INC) $(LDLIBS) $^ $(bin_out)$@

set2_binout := $(bin_path)set2$(bin_ext)
set2: $(set2_binout)
set2_test: set2
	$(set2_binout)
$(set2_binout): $(source_path)/cover.c \
								$(source_path)/list.c \
                $(source_path)/set.c \
                $(examples_path)/set/ex-2.c
	$(CC) $(CFLAGS) $(INC) $(LDLIBS) $^ $(bin_out)$@
