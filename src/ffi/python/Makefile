CFLAGS ?= -Wall -g 

pc.out: pc.c
	$(CC) $(CFLAGS) -o $@ $^

install: pc.out
	@(cp pc.out $(INSTALL_BIN)/pc.out)

run: pc.out
	./pc.out $(args)

debug: pc.out
	$(DEBUG) ./pc.out $(args)

clean:
	-(rm -f pc.out)
