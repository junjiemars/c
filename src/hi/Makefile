hi.out: hi.c
	$(CC) $(CFLAGS) hi.c -o hi.out

install: hi.out
	cp hi.out $(INSTALL_BIN)/hi

run: hi.out
	./hi.out $(ARGS)

debug: hi.out
	$(DEBUG) ./hi.out

clean:
	rm -f hi.out
