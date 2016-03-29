CFLAGS ?= -Wall -g 

str.out: str.c
	$(CC) $(CFLAGS) -o $@ $^

install: str.out
	@(cp str.out $(INSTALL_BIN)/utf8)

run: str.out
	./str.out $(args)

debug: str.out
	$(DEBUG) ./str.out $(args)

clean:
	-(rm -f str.out)
