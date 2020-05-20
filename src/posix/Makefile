# ./configure --has-posix

posix: posix_bits																\
       posix_tmp
posix_test: posix_bits_test											\
            posix_tmp_test

posix_prefix := posix
INC += -I$(posix_root)

# bits
posix_bits_binout := $(bin_path)$(posix_prefix)_bits$(bin_ext)

posix_bits: $(posix_bits_binout)
posix_bits_test: posix_bits
	$(posix_bits_binout)

$(posix_bits_binout): $(posix_root)bits_test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# msvc on Windows
ifeq ($(CC_NAME), msvc)
posix: posix_getopt
posix_getopt: $(src_path)getopt.h $(src_path)getopt.c
posix_getopt_repo = https://raw.githubusercontent.com/alex85k/wingetopt/master/src/

$(src_path)getopt.h: 
	curl -sLo $@ $(io_getopt_repo)getopt.h
$(src_path)getopt.c:
	curl -sLo $@ $(io_getopt_repo)getopt.c
endif # end of msvc

# tmp
posix_tmp_binout := $(bin_path)$(posix_prefix)_tmp$(bin_ext)

posix_tmp: $(posix_tmp_binout)
posix_tmp_test: posix_tmp
	$(posix_tmp_binout)

$(posix_tmp_binout): $(posix_root)tmp/tmp.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

