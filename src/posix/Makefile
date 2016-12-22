
ifeq ($(CC_NAME), msvc)

posix: posix_getopt

posix_getopt: $(src_path)getopt.h $(src_path)getopt.c
posix_getopt_repo = https://raw.githubusercontent.com/alex85k/wingetopt/master/src/

$(src_path)getopt.h: 
	curl -sLo $@ $(io_getopt_repo)getopt.h
$(src_path)getopt.c:
	curl -sLo $@ $(io_getopt_repo)getopt.c

endif
