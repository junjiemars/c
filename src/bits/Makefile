
.DEFAULT: bits.out

bits.out:
	$(CC) print.c -o bits.out

install: bits.out
	cp bits.out $(INSTALL_BIN)/bits

run: bits.out
	./bits.out

clean:
	rm -f bits.out

