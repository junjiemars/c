

io_binout := $(bin_path)io$(bin_ext)

io: $(io_binout)

io_inc := $(INC) -I$(src_path) -I$(src_path)file
io_c := $(src_path)file/sum.c

ifeq ($(NM_SYSTEM), MSYS_NT)
	io_inc += -I$(src_path)posix
	io_c += $(src_path)posix/getopt.c
	io_getopt_repo = https://raw.githubusercontent.com/alex85k/wingetopt/master/src/
$(src_path)posix/getopt.c $(src_path)posix/getopt.h: 
	curl -sLo $(src_path)posix/getopt.h $(io_getopt_repo)getopt.h
	curl -sLo $(src_path)posix/getopt.c $(io_getopt_repo)getopt.c
endif

$(io_binout): $(io_c) $(src_path)shell.c 
	$(CC) $(CFLAGS) $(io_inc) $^ $(bin_out)$@

io_test: io
	$(io_binout) --help
	$(io_binout) --type=file --output=$(tmp_path)sum.txt --input=$(tmp_path)seq.txt 
