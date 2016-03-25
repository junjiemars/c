utf8.out: utf8.c
	$(CC) $(CFLAGS) -o $@ $^

install: utf8.out
	@(cp utf8.out $(INSTALL_BIN)/utf8)

run: utf8.out
	./utf8.out $(args)

debug: utf8.out
	$(DEBUG) ./utf8.out $(args)

clean:
	-(rm -f utf8.out)
