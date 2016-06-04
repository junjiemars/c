CFLAGS ?= -Wall -g 

fibo.out: fibo.c
	$(CC) $(CFLAGS) -o $@ $^

install: fibo.out
	@(cp fibo.out $(INSTALL_BIN)/fibo)

run: fibo.out
	./fibo.out $(args)

debug: fibo.out
	$(DEBUG) ./fibo.out $(args)

clean:
	-(rm -f fibo.out)
