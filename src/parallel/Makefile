# -*- mode:makefile-gmake -*-
#
# ./configure --without-debug --has-parallel
#

parallel: parallel_openmp                       \
          parallel_pthread                      \
          parallel_atomic

parallel_test: parallel_openmp_test             \
               parallel_pthread_test            \
               parallel_atomic_test

# env
parallel_prefix := parallel

INC += $(nm_inc_opt)$(parallel_root) $(nm_inc_opt)$(root)/posix


ifeq (msvc, $(CC_NAME))
INC += -I$(root)/posix
getopt_c := $(root)/posix/getopt.c
endif # end of msvc checking


ifeq (1, $(_MEMORY_))
  ifeq (YES, $(has_sanitize))
    CFLAGS += $(cflags_sanitize)
  endif # end of has_sanitize
endif # end of _MEMORY_




# openmp
parallel_openmp_basic_binout := $(bin_path)/$(parallel_prefix)_openmp_basic$(bin_ext)
parallel_openmp_for_binout := $(bin_path)/$(parallel_prefix)_openmp_for$(bin_ext)

ifeq (YES, $(has_openmp))
parallel_openmp: parallel_openmp_basic								\
              parallel_openmp_for
parallel_openmp_test: parallel_openmp_basic_test			\
                   parallel_openmp_for_test
else
parallel_openmp:
	@echo "#skip parallel_openmp_test"
parallel_openmp_test: parallel_openmp
endif # end of has_openmp

parallel_openmp_basic: $(parallel_openmp_basic_binout)
parallel_openmp_basic_test: parallel_openmp_basic
	$(parallel_openmp_basic_binout)

$(parallel_openmp_basic_binout): $(parallel_root)/openmp/b.c
	$(CC) $(CFLAGS) $(INC) $(nm_openmp_opt) $^ $(bin_out)$@

parallel_openmp_for: $(parallel_openmp_for_binout)
parallel_openmp_for_test: parallel_openmp_for
	$(parallel_openmp_for_binout) 100
	$(parallel_openmp_for_binout) 10000
	$(parallel_openmp_for_binout) 1000000

$(parallel_openmp_for_binout): $(parallel_root)/openmp/for.c
	$(CC) $(CFLAGS) $(INC) $(nm_openmp_opt) $^ $(bin_out)$@



# pthread
parallel_pthread_basic_binout := $(bin_path)/$(parallel_prefix)_pthread_basic$(bin_ext)
parallel_pthread_exit_binout := $(bin_path)/$(parallel_prefix)_pthread_exit$(bin_ext)
parallel_pthread_deadlock_binout := $(bin_path)/$(parallel_prefix)_pthread_deadlock$(bin_ext)
parallel_pthread_detach_binout := $(bin_path)/$(parallel_prefix)_pthread_detach$(bin_ext)
parallel_pthread_mutex_binout := $(bin_path)/$(parallel_prefix)_pthread_mutex$(bin_ext)
parallel_pthread_stacksize_binout := $(bin_path)/$(parallel_prefix)_pthread_stacksize$(bin_ext)
parallel_pthread_private_binout := $(bin_path)/$(parallel_prefix)_pthread_private$(bin_ext)
parallel_pthread_wait_binout := $(bin_path)/$(parallel_prefix)_pthread_wait$(bin_ext)
parallel_pthread_once_binout := $(bin_path)/$(parallel_prefix)_pthread_once$(bin_ext)
parallel_pthread_mutex1_binout := $(bin_path)/$(parallel_prefix)_pthread_mutex1$(bin_ext)

ifeq (YES, $(has_pthread))
parallel_pthread: parallel_pthread_basic        \
                  parallel_pthread_deadlock     \
                  parallel_pthread_detach       \
                  parallel_pthread_exit         \
                  parallel_pthread_mutex        \
                  parallel_pthread_mutex1       \
                  parallel_pthread_private      \
                  parallel_pthread_stacksize    \
                  parallel_pthread_wait         \
                  parallel_pthread_once
parallel_pthread_test: parallel_pthread_basic_test      \
                       parallel_pthread_deadlock_test   \
                       parallel_pthread_detach_test     \
                       parallel_pthread_exit_test       \
                       parallel_pthread_mutex_test      \
                       parallel_pthread_mutex1_test     \
                       parallel_pthread_private_test    \
                       parallel_pthread_stacksize_test  \
                       parallel_pthread_wait_test       \
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

parallel_pthread_mutex1: $(parallel_pthread_mutex1_binout)
parallel_pthread_mutex1_test: parallel_pthread_mutex1
	$(parallel_pthread_mutex1_binout)

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

$(parallel_pthread_basic_binout): $(parallel_root)/pthread/basic.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_deadlock_binout): $(parallel_root)/pthread/deadlock.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_detach_binout): $(parallel_root)/pthread/detach.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_exit_binout): $(parallel_root)/pthread/exit.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_mutex_binout): $(parallel_root)/pthread/mutex.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_mutex1_binout): $(parallel_root)/pthread/mutex1.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_stacksize_binout): $(parallel_root)/pthread/stacksize.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_private_binout): $(parallel_root)/pthread/private.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_wait_binout): $(parallel_root)/pthread/wait.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@

$(parallel_pthread_once_binout): $(parallel_root)/pthread/once.c
	$(CC) $(CFLAGS) $(INC) $(fpthread) $^ $(bin_out)$@



# atomic
parallel_atomic_bone_binout := $(bin_path)/$(parallel_prefix)_atomic_bone$(bin_ext)
parallel_atomic_counter_binout := $(bin_path)/$(parallel_prefix)_atomic_counter$(bin_ext)

parallel_atomic: $(parallel_atomic_bone_binout)
parallel_atomic_test: parallel_atomic_bone_test

parallel_atomic_bone_test: $(parallel_atomic_bone_binout)
	$(parallel_atomic_bone_binout)


$(parallel_atomic_bone_binout): $(parallel_root)/atomic/b1.c
	$(CC) $(CPPLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

ifeq ($(has_pthread),YES)
parallel_atomic_counter_test: $(parallel_atomic_counter_binout)
	$(parallel_atomic_counter_binout) 4

$(parallel_atomic_counter_binout): $(parallel_root)/atomic/a1.c
	$(CC) $(CPPLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@
endif



# eof
