mp: openmp

mp_test: openmp_test

mp_prefix := mp

INC += -I$(mp_root)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
CFLAGS += -openmp
endif


# openmp
openmp_binout := $(bin_path)$(mp_prefix)_openmp$(bin_ext)

openmp: $(openmp_binout)
openmp_test: openmp
	$(openmp_binout)

$(openmp_binout): $(mp_root)openmp/o.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

