hi.out: hi.c
	$(CC) hi.c -o hi.out

install: hi.out
	cp hi.out $(INSTALL_BIN)/hi

run: hi.out
	./hi.out $(ARGS)

clean:
	rm -f hi.out
