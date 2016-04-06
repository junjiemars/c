CFLAGS ?= -Wall -g 

endian.out: endian.c
	$(CC) $(CFLAGS) -o $@ $^

install: endian.out
	@(cp $^ $(INSTALL_BIN)/endian)

run: endian.out
	./$^ $(args)

debug: endian.out
	$(DEBUG) ./$^ $(args)

clean:
	-(rm -f endian.out)
