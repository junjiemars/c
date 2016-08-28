

${CL_BIN_PATH}/hi: ${stick}/hi.c
	$(CC) $(CFLAGS) ${stick}/hi.c -o ${CL_BIN_PATH}hi

install: hi.out
	@(cp hi.out $(INSTALL_BIN)/hi)

run: hi.out
	./hi.out $(args)

debug: hi.out
	$(DEBUG) ./hi.out $(args)

clean:
	-(rm -rf hi.out hi.out.*)
