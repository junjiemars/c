CFLAGS ?= -Wall -g 

calr.out: calr.s
	$(CC) $(CFLAGS) -o $@ $^

calr.s: calr.i
	$(CC) -S -o $@ $^

calr.i: calr.c
	$(CC) -E -o $@ $^

install: calr.out
	@(cp calr.out $(INSTALL_BIN)/mem)

run: calr.out
	./calr.out $(args)

debug: calr.out
	$(DEBUG) ./calr.out $(args)

clean:
	-(rm -f calr.out calr.s calr.i)
