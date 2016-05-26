

libd.out: libd.c share$(LIB_SUFFIX)
	$(CC) $(CFLAGS) -o $@ $^

share$(LIB_SUFFIX):
	@(cd share && $(MAKE) share$(LIB_SUFFIX))

install: libd.out
	@(cp share$(LIB_SUFFIX) $(INSTALL_BIN)/share$(LIB_SUFFIX))
	@(cp libd.out $(INSTALL_BIN)/libd)

run: libd.out
	DYLD_LIBRARY_PATH=share ./libd.out $(args)

debug: libd.out
	$(DEBUG) ./libd.out $(args)

clean:
	-(cd share && $(MAKE) clean)
	-(rm -rf libd.out* share$(LIB_SUFFIX)*)
