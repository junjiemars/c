
fibo_binout := $(bin_path)fibo$(bin_ext)

fibo_cflags := $(CFLAGS) $(INC) -I$(src_path)
fibo_getopt_c :=

ifeq ($(CC_NAME), msvc)
	fibo_cflags += -I$(root)posix
	fibo_getopt_c := $(root)posix/getopt.c
endif

fibo: $(fibo_binout)
fibo_test: fibo
	$(fibo_binout)
	$(fibo_binout) --static
	$(fibo_binout) --tail

$(fibo_binout): $(src_path)fibo.c
	$(CC) $(fibo_cflags) $(fibo_getopt_c) $^ $(bin_out)$@
