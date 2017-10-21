
str: str1

str_test: str_test


INC += -I$(str_root)

# str
str_binout := $(bin_path)str$(bin_ext)

str1: $(str_binout)
str_test: str1
	$(str_binout)

$(str_binout): $(str_root)str.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
