CFLAGS ?= -Wall -g 

mem.out: mem.c
	$(CC) $(CFLAGS) -o $@ $^

install: mem.out
	@(cp mem.out $(INSTALL_BIN)/utf8)

run: mem.out
	./mem.out $(args)

debug: mem.out
	$(DEBUG) ./mem.out $(args)

clean:
	-(rm -f mem.out)
