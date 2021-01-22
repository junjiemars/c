#
# ./configure --without-debug --has-parallel
#

parallel: parallel_omp													\
					parallel_pthread_basic

parallel_test: parallel_omp_test								\
							 parallel_pthread_test

parallel_prefix := parallel
INC += -I$(parallel_root)


ifeq ($(CC_NAME),msvc)
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif # end of msvc checking


ifeq ($(_MEMORY_),1)
ifeq ($(has_sanitize),YES)
CFLAGS += $(cflags_sanitize)
endif # end of has_sanitize
endif # end of _MEMORY_


# openmp
parallel_omp_basic_binout := $(bin_path)$(parallel_prefix)_omp_basic$(bin_ext)
parallel_omp_for_binout := $(bin_path)$(parallel_prefix)_omp_for$(bin_ext)

ifeq ($(has_openmp),YES)
parallel_omp: parallel_omp_basic								\
              parallel_omp_for
parallel_omp_test: parallel_omp_basic_test			\
                   parallel_omp_for_test
CFLAGS += $(cflags_openmp)
else
parallel_omp:
	@echo "#skip parallel_omp_test"
parallel_omp_test: parallel_omp
endif # end of has_openmp

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

ifeq ($(has_pthread),YES)
parallel_pthread: parallel_pthread_basic
parallel_pthread_test: parallel_pthread_basic_test
else
parallel_pthread:
	@echo "#skip parallel_pthread_test ..."
parallel_pthread_test: parallel_pthread
endif # end of has_pthread

parallel_pthread_basic: $(parallel_pthread_basic_binout)
parallel_pthread_basic_test: parallel_pthread_basic
	$(parallel_pthread_basic_binout)

$(parallel_pthread_basic_binout): $(parallel_root)pthread/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
