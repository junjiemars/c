#
# ./configure --has-posix
#

posix: posix_bits                               \
       posix_defs                               \
       posix_getopt                             \
       posix_ints                               \
       posix_strs

posix_test: posix_bits_test                     \
            posix_defs_test                     \
            posix_getopt_test                   \
            posix_ints_test                     \
            posix_strs_test


# env
posix_prefix := posix
INC += -I$(posix_root)


# bits
posix_bits_binout := $(bin_path)/$(posix_prefix)_bits$(bin_ext)

posix_bits: $(posix_bits_binout)
posix_bits_test: posix_bits
	$(posix_bits_binout)

$(posix_bits_binout): $(posix_root)/bits_test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# getopt
posix_getopt_binout := $(bin_path)/$(posix_prefix)_getopt$(bin_ext)

posix_getopt: $(posix_getopt_binout)
posix_getopt_test: posix_getopt
	$(posix_getopt_binout) -rabc -o123 -n	-N

posix_getopt_c :=
ifeq ($(CC_NAME), msvc)
posix_getopt_h := $(posix_root)/getopt.h
posix_getopt_c := $(posix_root)/getopt.c
posix_getopt_repo = https://raw.githubusercontent.com/alex85k/wingetopt/master/src/

$(posix_getopt_h):
	curl -sLo $@ $(posix_getopt_repo)getopt.h
$(posix_getopt_c):
	curl -sLo $@ $(posix_getopt_repo)getopt.c
endif # end of msvc

$(posix_getopt_binout): $(posix_root)/getopt_test.c $(posix_getopt_c)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# defs
posix_defs_binout := $(bin_path)/$(posix_prefix)_defs$(bin_ext)

posix_defs: $(posix_defs_binout)
posix_defs_test: posix_defs
	$(posix_defs_binout)

$(posix_defs_binout): $(posix_root)/defs_test.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@

# ints
posix_ints_binout := $(bin_path)/$(posix_prefix)_ints$(bin_ext)

posix_ints: $(posix_ints_binout)
posix_ints_test: posix_ints
	$(posix_ints_binout)

$(posix_ints_binout): $(posix_root)/ints_test.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@


# strs
posix_strs_binout := $(bin_path)/$(posix_prefix)_strs$(bin_ext)

posix_strs: $(posix_strs_binout)
posix_strs_test: posix_strs
	$(posix_strs_binout)

$(posix_strs_binout): $(posix_root)/strs_test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# mmap
posix_mmap_read_binout := $(bin_path)/$(posix_prefix)_mmap_read$(bin_ext)
posix_mmap_shared_binout := $(bin_path)/$(posix_prefix)_mmap_shared$(bin_ext)

posix_mmap: posix_mmap_read                     \
            posix_mmap_shared
posix_mmap_test: posix_mmap_read_test           \
                 posix_mmap_shared_test

posix_mmap_read: $(posix_mmap_read_binout)
posix_mmap_read_test: posix_mmap_read
	$(posix_mmap_read_binout) $(CURDIR)/src/posix/mmap/dout.random 2048

posix_mmap_shared: $(posix_mmap_shared_binout)
posix_mmap_shared_test: posix_mmap_shared
	$(posix_mmap_shared_binout) $(CURDIR)/src/posix/mmap/dout.random 2048

$(posix_mmap_read_binout): $(posix_root)/mmap/read.c		\
                           $(posix_root)/mmap/_mmap_.h
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@

$(posix_mmap_shared_binout): $(posix_root)/mmap/shared.c	\
                             $(posix_root)/mmap/_mmap_.h
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@


# sysconf
posix_sysconf_binout := $(bin_path)/$(posix_prefix)_sysconf$(bin_ext)

posix_sysconf: $(posix_sysconf_binout)
posix_sysconf_test: posix_sysconf
	$(posix_sysconf_binout)

$(posix_sysconf_binout): $(posix_root)/sysconf/c1.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@


# tmp
posix_tmp_binout := $(bin_path)/$(posix_prefix)_tmp$(bin_ext)

posix_tmp: $(posix_tmp_binout)
posix_tmp_test: posix_tmp
	$(posix_tmp_binout)

$(posix_tmp_binout): $(posix_root)/tmp/tmp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# eof
