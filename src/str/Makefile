
str: basic

str_test: basic_test


INC += -I$(str_root)

# str
basic_binout := $(bin_path)string-basic$(bin_ext)

basic: $(basic_binout)
basic_test: basic 
	$(basic_binout)

$(basic_binout): $(str_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
