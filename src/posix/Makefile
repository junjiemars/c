# -*- mode:makefile-gmake -*-
#
# ./configure --has-posix
#

posix: posix_npstd                              \
       posix_ndef                               \
       posix_nint                               \
       posix_nstr                               \
       posix_ncstd                              \
       posix_nustd                              \
       posix_nio                                \
       posix_nlim                               \
       posix_nbits                              \
       posix_getopt                             \
       posix_raw

posix_test: posix_npstd_test                    \
            posix_ndef_test                     \
            posix_nint_test                     \
            posix_nstr_test                     \
            posix_ncstd_test                    \
            posix_nustd_test                    \
            posix_nio_test                      \
            posix_nlim_test                     \
            posix_nbits_test                    \
            posix_getopt_test                   \
            posix_raw_test


# env
posix_prefix := posix

INC += -I$(posix_root)

ifeq ($(_MEMORY_), 1)
CFLAGS += $(f_sanitize)
endif # end of _MEMORY_



# npstd
posix_npstd_binout := $(bin_path)/$(posix_prefix)_npstd$(bin_ext)

posix_npstd: $(posix_npstd_binout)
posix_npstd_test: posix_npstd
	$(posix_npstd_binout)

$(posix_npstd_binout): $(posix_root)/npstd_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@

# nasrt
posix_nasrt_binout := $(bin_path)/$(posix_prefix)_nasrt$(bin_ext)
posix_nasrt_cppout := $(tmp_path)/$(posix_prefix)_nasrt$(cpp_ext)

posix_nasrt: $(posix_nasrt_binout)
posix_nasrt_test: posix_nasrt
	$(posix_nasrt_binout)

$(posix_nasrt_binout): $(posix_nasrt_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(posix_nasrt_cppout): $(posix_root)/nasrt_test.c
	$(CC) $(CPPFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# nbits
posix_nbits_binout := $(bin_path)/$(posix_prefix)_nbits$(bin_ext)
posix_nbits_cppout := $(tmp_path)/$(posix_prefix)_nbits$(cpp_ext)

posix_nbits: $(posix_nbits_binout)
posix_nbits_test: posix_nbits
	$(posix_nbits_binout)

$(posix_nbits_binout): $(posix_nbits_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(posix_nbits_cppout): $(posix_root)/nbits_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


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

# nlim
posix_nlim_binout := $(bin_path)/$(posix_prefix)_nlim$(bin_ext)

posix_nlim: $(posix_nlim_binout)
posix_nlim_test: posix_nlim
	$(posix_nlim_binout)

$(posix_nlim_binout): $(posix_root)/nlim_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $^ $(bin_out)$@


# ndef
posix_ndef_binout := $(bin_path)/$(posix_prefix)_ndef$(bin_ext)
posix_ndef_cppout := $(tmp_path)/$(posix_prefix)_ndef$(cpp_ext)

posix_ndef: $(posix_ndef_binout)
posix_ndef_test: posix_ndef
	$(posix_ndef_binout)

$(posix_ndef_binout): $(posix_ndef_cppout)
	$(CC) $(CFLAGS) $< $(bin_out)$@

$(posix_ndef_cppout): $(posix_root)/ndef_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $< $(cpp_out)$@


# nint
posix_nint_binout := $(bin_path)/$(posix_prefix)_nint$(bin_ext)
posix_nint_cppout := $(tmp_path)/$(posix_prefix)_nint$(cpp_ext)

posix_nint: $(posix_nint_binout)
posix_nint_test: posix_nint
	$(posix_nint_binout)

$(posix_nint_binout): $(posix_nint_cppout)
	$(CC) $(CFLAGS) $< $(bin_out)$@

$(posix_nint_cppout): $(posix_root)/nint_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $< $(cpp_out)$@



# nio
posix_nio_binout := $(bin_path)/$(posix_prefix)_nio$(bin_ext)
posix_nio_cppout := $(tmp_path)/$(posix_prefix)_nio$(cpp_ext)

posix_nio: $(posix_nio_binout)
posix_nio_test: posix_nio
	$(posix_nio_binout) $(CURDIR)/$(posix_root)/nio_test.c

$(posix_nio_binout): $(posix_root)/nio.c        \
                     $(posix_root)/nio_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(bin_out)$@ $^



# nstr
posix_nstr_binout := $(bin_path)/$(posix_prefix)_nstr$(bin_ext)
posix_nstr_cppout := $(tmp_path)/$(posix_prefix)_nstr$(cpp_ext)

posix_nstr: $(posix_nstr_binout)
posix_nstr_test: posix_nstr
	$(posix_nstr_binout)

$(posix_nstr_binout): $(posix_nstr_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(posix_nstr_cppout): $(posix_root)/nstr_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


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


# ncstd
posix_ncstd_binout := $(bin_path)/$(posix_prefix)_ncstd$(bin_ext)
posix_ncstd_cppout := $(tmp_path)/$(posix_prefix)_ncstd$(cpp_ext)

posix_ncstd: $(posix_ncstd_binout)
posix_ncstd_test: posix_ncstd
	$(posix_ncstd_binout)

$(posix_ncstd_binout): $(posix_ncstd_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(posix_ncstd_cppout): $(posix_root)/ncstd_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@


# nustd
posix_nustd_binout := $(bin_path)/$(posix_prefix)_nustd$(bin_ext)
posix_nustd_cppout := $(tmp_path)/$(posix_prefix)_nustd$(cpp_ext)

posix_nustd: $(posix_nustd_binout)
posix_nustd_test: posix_nustd
	-$(posix_nustd_binout)

$(posix_nustd_binout): $(posix_nustd_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(posix_nustd_cppout): $(posix_root)/nustd_test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) $(nm_stage_pre) $^ $(cpp_out)$@

# raw
posix_raw_winnt_binout := $(bin_path)/$(posix_prefix)_raw_winnt$(bin_ext)
posix_raw_darwin_binout := $(bin_path)/$(posix_prefix)_raw_darwin$(bin_ext)
posix_raw_linux_binout := $(bin_path)/$(posix_prefix)_raw_linux$(bin_ext)

ifeq ($(NM_SYSTEM), WinNT)
posix_raw: posix_raw_winnt
posix_raw_test: posix_raw
	-$(posix_raw_winnt_binout)
else
ifeq ($(NM_SYSTEM), Darwin)
posix_raw: posix_raw_darwin
posix_raw_test: posix_raw
	$(posix_raw_darwin_binout)
else
ifeq ($(NM_SYSTEM), Linux)
posix_raw: posix_raw_darwin
posix_raw_test: posix_raw
	$(posix_raw_darwin_binout)
else
posix_raw:
	@echo "#skip $@ ..."
posix_raw_test: posix_raw
	@echo "#skip $@ ..."
endif														# Linux
endif														# Darwin
endif														# WinNT

posix_raw_winnt: $(posix_raw_winnt_binout)
posix_raw_darwin: $(posix_raw_darwin_binout)
posix_raw_linux: $(posix_raw_linux_binout)

$(posix_raw_winnt_binout): $(posix_root)/raw_winnt.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^
$(posix_raw_darwin_binout): $(posix_root)/raw_darwin.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^
$(posix_raw_linux_binout): $(posix_root)/raw_linux.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^



.PHONY: posix_npstd posix_npstd_test            \
        posix_ndef posix_ndef_test              \
        posix_nint posix_nint_test              \
        posix_nstr posix_nstr_test              \
        posix_ncstd posix_ncstd_test            \
        posix_nustd posix_nustd_test            \
        posix_nio posix_nio_test                \
        posix_nlim posix_nlim_test              \
        posix_nbits posix_nbits_test            \
        posix_getopt posix_getopt_test          \
        posix_raw posix_raw_test


# eof
