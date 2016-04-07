CFLAGS ?= -Wall -g 

env.out: env.c
	$(CC) $(CFLAGS) -o $@ $^

install: env.out
	@(cp $^ $(INSTALL_BIN)/env)

run: env.out
	./$^ $(args)

debug: env.out
	$(DEBUG) ./$^ $(args)

clean:
	-(rm -f env.out)
