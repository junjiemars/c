CFLAGS ?= -Wall -g 

tm.out: tm.c driver.c
	$(CC) $(CFLAGS) -o $@ $^

install: tm.out
	@(cp $^ $(INSTALL_BIN)/tm)

run: tm.out
	./$^ $(args)

debug: tm.out
	$(DEBUG) ./$^ $(args)

clean:
	-(rm -f tm.out)

