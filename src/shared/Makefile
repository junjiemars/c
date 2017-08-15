
shared: geo math
shared_test: geo_test math_test


INC += -I$(src_path)

# geo
geo_libout := $(lib_path)libgeo$(lib_ext)
geo_binout := $(tmp_path)geo$(bin_ext)

geo: $(geo_libout)
geo_test: geo $(geo_binout)
	$(geo_binout)

$(geo_binout): $(src_path)geo/geo.c $(src_path)geo/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(geo_libout): $(src_path)geo/geo.c
	$(CC) $(CFLAGS) $(INC) $(nm_pic_opt) $(nm_shared_opt) $^ $(bin_out)$@
	cp $(src_path)geo/geo.h $(inc_path)

# math
math_binout := $(bin_path)math$(bin_ext)

math: geo $(math_binout)

ifeq ($(CC_NAME), msvc)
math_lib_path := PATH
math_ldflags =
LDLIBS = $(lib_path)libgeo.lib
else
math_lib_path := LD_LIBRARY_PATH
math_ldflags = $(LDFLAGS)
LDLIBS = -lgeo
endif

math_test: math
	$(math_lib_path)=$(lib_path) $(math_binout)

$(math_binout): $(src_path)math/math1.c 
	$(CC) $(CFLAGS) $(INC) $(math_ldflags) $(LDLIBS) $^ $(bin_out)$@ 

