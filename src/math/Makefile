
math_cflags := $(CFLAGS) -std=c99

$(tmp_path)math.o: $(src_path)math1.c
	$(CC) -c $(math_cflags) -o $(tmp_path)math.o $(src_path)math1.c

$(bin_path)math: $(tmp_path)math.o
	$(LINK) -o $(bin_path)math $(tmp_path)math.o
