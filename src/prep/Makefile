CFLAGS ?= -Wall -g 

prep.out: prep.c
	$(CC) $(CFLAGS) -o $@ $^

install: prep.out
	@(cp $^ $(INSTALL_BIN)/prep)

run: prep.out
	./$^ $(args)

debug: prep.out
	$(DEBUG) ./$^ $(args)

clean:
	-(rm -f prep.out)
