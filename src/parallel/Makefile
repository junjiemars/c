#
# ./configure --without-debug --has-parallel
#

parallel: parallel_omp													\
					parallel_pthread_basic

parallel_test: parallel_omp_test								\
							 parallel_pthread_test

parallel_prefix := parallel
INC += -I$(parallel_root)


ifeq (msvc, $(CC_NAME))
INC += -I$(root)posix
getopt_c := $(root)posix/getopt.c
endif # end of msvc checking


ifeq (1, $(_MEMORY_))
ifeq (YES, $(has_sanitize)))
CFLAGS += $(cflags_sanitize)
endif # end of has_sanitize
endif # end of _MEMORY_


# openmp
parallel_omp_basic_binout := $(bin_path)$(parallel_prefix)_omp_basic$(bin_ext)
parallel_omp_for_binout := $(bin_path)$(parallel_prefix)_omp_for$(bin_ext)

ifeq (YES, $(has_openmp))
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
parallel_pthread_exit_binout := $(bin_path)$(parallel_prefix)_pthread_exit$(bin_ext)
parallel_pthread_deadlock_binout := $(bin_path)$(parallel_prefix)_pthread_deadlock$(bin_ext)
parallel_pthread_detach_binout := $(bin_path)$(parallel_prefix)_pthread_detach$(bin_ext)
parallel_pthread_mutex_binout := $(bin_path)$(parallel_prefix)_pthread_mutex$(bin_ext)
parallel_pthread_stacksize_binout := $(bin_path)$(parallel_prefix)_pthread_stacksize$(bin_ext)
parallel_pthread_private_binout := $(bin_path)$(parallel_prefix)_pthread_private$(bin_ext)
parallel_pthread_wait_binout := $(bin_path)$(parallel_prefix)_pthread_wait$(bin_ext)
parallel_pthread_once_binout := $(bin_path)$(parallel_prefix)_pthread_once$(bin_ext)

ifeq (YES, $(has_pthread))
parallel_pthread: parallel_pthread_basic				\
                  parallel_pthread_deadlock			\
                  parallel_pthread_detach				\
                  parallel_pthread_exit					\
                  parallel_pthread_mutex				\
                  parallel_pthread_private			\
                  parallel_pthread_stacksize		\
                  parallel_pthread_wait					\
                  parallel_pthread_once
parallel_pthread_test: parallel_pthread_basic_test			\
                       parallel_pthread_deadlock_test		\
                       parallel_pthread_detach_test			\
                       parallel_pthread_exit_test				\
                       parallel_pthread_mutex_test			\
                       parallel_pthread_private_test		\
                       parallel_pthread_stacksize_test	\
                       parallel_pthread_wait_test				\
                       parallel_pthread_once_test
else
parallel_pthread:
	@echo "#skip parallel_pthread_test ..."
parallel_pthread_test: parallel_pthread
endif # end of has_pthread

parallel_pthread_basic: $(parallel_pthread_basic_binout)
parallel_pthread_basic_test: parallel_pthread_basic
	$(parallel_pthread_basic_binout)

parallel_pthread_deadlock: $(parallel_pthread_deadlock_binout)
parallel_pthread_deadlock_test: parallel_pthread_deadlock
	$(parallel_pthread_deadlock_binout) #without deadlock
	$(parallel_pthread_deadlock_binout) 1 #with deadlock

parallel_pthread_detach: $(parallel_pthread_detach_binout)
parallel_pthread_detach_test: parallel_pthread_detach
	$(parallel_pthread_detach_binout)

parallel_pthread_exit: $(parallel_pthread_exit_binout)
parallel_pthread_exit_test: parallel_pthread_exit
	$(parallel_pthread_exit_binout)

parallel_pthread_mutex: $(parallel_pthread_mutex_binout)
parallel_pthread_mutex_test: parallel_pthread_mutex
	$(parallel_pthread_mutex_binout)	 # without mutex
	$(parallel_pthread_mutex_binout) 1 # with mutex

parallel_pthread_private: $(parallel_pthread_private_binout)
parallel_pthread_private_test: parallel_pthread_private
	$(parallel_pthread_private_binout)

parallel_pthread_stacksize: $(parallel_pthread_stacksize_binout)
parallel_pthread_stacksize_test: parallel_pthread_stacksize
	$(parallel_pthread_stacksize_binout)

parallel_pthread_wait: $(parallel_pthread_wait_binout)
parallel_pthread_wait_test: parallel_pthread_wait
	$(parallel_pthread_wait_binout)

parallel_pthread_once: $(parallel_pthread_once_binout)
parallel_pthread_once_test: parallel_pthread_once
	$(parallel_pthread_once_binout)

$(parallel_pthread_basic_binout): $(parallel_root)pthread/basic.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_deadlock_binout): $(parallel_root)pthread/deadlock.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_detach_binout): $(parallel_root)pthread/detach.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_exit_binout): $(parallel_root)pthread/exit.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_mutex_binout): $(parallel_root)pthread/mutex.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_stacksize_binout): $(parallel_root)pthread/stacksize.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_private_binout): $(parallel_root)pthread/private.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_wait_binout): $(parallel_root)pthread/wait.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(parallel_pthread_once_binout): $(parallel_root)pthread/once.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# EOF
