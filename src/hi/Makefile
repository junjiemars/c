hi.out: hi.c
	$(CC) $(CFLAGS) hi.c -o hi.out

install: hi.out
	@(cp hi.out $(INSTALL_BIN)/hi)

run: hi.out
	./hi.out $(args)

debug: hi.out
	$(DEBUG) ./hi.out $(args)

clean:
	-(rm -rf hi.out hi.out.*)
