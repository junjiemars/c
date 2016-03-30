CFLAGS ?= -Wall -g 

math.out: math1.c
	$(CC) $(CFLAGS) -o $@ $^

install: math.out
	@(cp $^ $(INSTALL_BIN)/math)

run: math.out
	./$^ $(args)

debug: math.out
	$(DEBUG) ./$^ $(args)

clean:
	-(rm -f math.out)
