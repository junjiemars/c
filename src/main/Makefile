
main_binout := $(bin_path)main$(bin_ext)

main: $(main_binout)
main_test: main
	$(main_binout) a bb ccc 

$(main_binout): $(src_path)m.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
