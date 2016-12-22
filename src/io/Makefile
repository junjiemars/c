

io_binout := $(bin_path)io$(bin_ext)

io: $(io_binout)

io_cflags := $(CFLAGS)
io_inc := $(INC) -I$(src_path) -I$(src_path)file
io_c := $(src_path)file/sum.c

ifeq ($(CC_NAME), msvc)
	io_inc += -I$(src_root)posix
	io_c += $(src_root)posix/getopt.c
endif

ifeq ($(CC_NAME), gcc)
	io_cflags += -Wno-unused-result
endif

$(io_binout): $(io_c) $(src_path)shell.c 
	$(CC) $(io_cflags) $(io_inc) $^ $(bin_out)$@

io_test: io
	$(io_binout) --help
	$(io_binout) --type=file --output=$(tmp_path)sum.txt --input=$(tmp_path)seq.txt 
