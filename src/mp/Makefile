mp: openmp_basic \
		openmp_for

mp_test: openmp_basic_test \
				 openmp_for_test

mp_prefix := mp

INC += -I$(mp_root)

ifeq ($(CC_NAME), msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif


# openmp
openmp_basic_binout := $(bin_path)$(mp_prefix)_openmp_basic$(bin_ext)

openmp_basic: $(openmp_basic_binout)
openmp_basic_test: openmp_basic
	$(openmp_basic_binout)

$(openmp_basic_binout): $(mp_root)openmp/b.c
	$(CC) $(CFLAGS) $(nm_openmp_opt) $(INC) $^ $(bin_out)$@

openmp_for_binout := $(bin_path)$(mp_prefix)_openmp_for$(bin_ext)

openmp_for: $(openmp_for_binout)
openmp_for_test: openmp_for
	$(openmp_for_binout) 1000000

$(openmp_for_binout): $(mp_root)openmp/for.c
	$(CC) $(CFLAGS) $(INC) $(nm_openmp_opt) $^ $(bin_out)$@

