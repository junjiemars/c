#
# ./configure --without-debug --has-parallel
#

parallel: parallel_omp_basic \
					parallel_omp_for \
					parallel_pthread_basic

parallel_test: parallel_omp_basic_test \
							 parallel_omp_for_test \
							 parallel_pthread_basic_test

parallel_prefix := parallel
INC += -I$(parallel_root)


ifeq ($(CC_NAME),msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif # end of msvc checking


# openmp
parallel_omp_basic_binout := $(bin_path)$(parallel_prefix)_omp_basic$(bin_ext)
parallel_omp_for_binout := $(bin_path)$(parallel_prefix)_omp_for$(bin_ext)

parallel_omp: parallel_omp_basic								\
              parallel_omp_for
parallel_omp_test: parallel_omp_basic_test			\
                   parallel_omp_for_test

parallel_omp_basic: $(parallel_omp_basic_binout)
parallel_omp_basic_test: parallel_omp_basic
	$(parallel_omp_basic_binout)

$(parallel_omp_basic_binout): $(parallel_root)openmp/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

parallel_omp_for: $(parallel_omp_for_binout)
parallel_omp_for_test: parallel_omp_for
	$(parallel_omp_for_binout) 100
	$(parallel_omp_for_binout) 10000
	$(parallel_omp_for_binout) 1000000

$(parallel_omp_for_binout): $(parallel_root)openmp/for.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# pthread
parallel_pthread_basic_binout := $(bin_path)$(parallel_prefix)_pthread_basic$(bin_ext)

parallel_pthread: parallel_pthread_basic
parallel_pthread_test: parallel_pthread_basic_test

parallel_pthread_basic: $(parallel_pthread_basic_binout)
parallel_pthread_basic_test: parallel_pthread_basic
	$(parallel_pthread_basic_binout)

$(parallel_pthread_basic_binout): $(parallel_root)pthread/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
