CFLAGS ?= -Wall -g -dynamiclib -std=c99

share.dylib: share.c
	$(CC) $(CFLAGS) share.c -o share.dylib
	@(cp $@ ../)

install: share.dylib
	@(cp $^ $(INSTALL_BIN)/share.dylib)

clean:
	-(rm -rf share.dylib share.dylib.dSYM)
