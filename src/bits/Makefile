
.DEFAULT: bits.out

bits.out: bits.c
	$(CC) $(CFLAGS) bits.c -o bits.out

install: bits.out
	@(cp bits.out $(INSTALL_BIN)/bits)

run: bits.out
	./bits.out

debug: bits.out
	$(DEBUG) ./bits.out

clean:
	-(rm -rf bits.out bits.out.*)

