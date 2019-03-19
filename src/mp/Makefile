mp: openmp

mp_test: openmp_test

mp_prefix := mp

INC += -I$(mp_root)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif


# openmp
openmp_binout := $(bin_path)$(mp_prefix)_openmp$(bin_ext)

openmp: $(openmp_binout)
openmp_test: openmp
	$(openmp_binout)
	$(openmp_binout) 10000

$(openmp_binout): $(mp_root)openmp/o.c
	$(CC) $(CFLAGS) $(nm_openmp_opt) $(INC) $^ $(bin_out)$@

