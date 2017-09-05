
io: basic
io_test: basic_test

INC += -I$(src_path)

# basic I/O
basic_binout := $(bin_path)basic$(bin_ext)
basic_test: basic
	$(basic_binout)
basic: $(basic_binout)

$(basic_binout): $(src_path)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

#io_binout := $(bin_path)io$(bin_ext)
#
#io: $(io_binout)
#
#io_cflags := $(CFLAGS)
#io_inc := $(INC) -I$(src_path) -I$(src_path)file
#io_c := $(src_path)file/sum.c
#
#ifeq ($(CC_NAME), msvc)
#	io_inc += -I$(root)posix
#	io_c += $(root)posix/getopt.c
#endif
#
#ifeq ($(CC_NAME), gcc)
#	io_cflags += -Wno-unused-result
#endif
#
#$(io_binout): $(io_c) $(src_path)shell.c 
#	$(CC) $(io_cflags) $(io_inc) $^ $(bin_out)$@
#
#io_test: io
#	$(io_binout) --help
#	$(io_binout) --type=file --output=$(tmp_path)sum.txt --input=$(tmp_path)seq.txt 
