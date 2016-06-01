CFLAGS ?= -Wall -g 

scope.out: scope.c
	$(CC) $(CFLAGS) $^ -o $@

install: scope.out
	@(cp scope.out $(INSTALL_BIN)/scope)

run: scope.out
	./scope.out $(args)

debug: scope.out
	$(DEBUG) ./scope.out $(args)

clean:
	-(rm -f scope.out)
