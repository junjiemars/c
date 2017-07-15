
math_binout := $(bin_path)math$(bin_ext)

math: geo $(math_binout)
math_test: math
	LD_LIBRARY_PATH=$(lib_path) $(math_binout)

math_cflags = $(CFLAGS) $(INC) -std=c99
math_ldlibs = $(LDLIBS) -lgeo

$(math_binout): $(src_path)math1.c 
	$(LINK) $(math_cflags) $^ $(bin_out)$@ $(math_ldlibs) 

