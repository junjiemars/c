CFLAGS ?= -Wall -g 

type.out: t.c
	$(CC) $(CFLAGS) -o $@ $^

install: type.out
	@(cp $^ $(INSTALL_BIN)/type)

run: type.out
	./$^ $(args)

debug: type.out
	$(DEBUG) ./$^ $(args)

clean:
	-(rm -f type.out)
