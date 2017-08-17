
library: geo math
library_test: geo_test math_test


INC += -I$(src_path)

geo: geo_static 
geo_test: geo_static_test 


# geo
geo_arout := $(lib_path)geo$(ar_ext)
geo_binout := $(tmp_path)geo$(bin_ext)
geo_objout := $(tmp_path)geo$(obj_ext)
geo_libout := $(lib_path)libgeo$(lib_ext)

geo_static: $(geo_arout)
geo_static_test: $(geo_binout)
	$(geo_binout)
geo_shared: $(geo_libout)

$(geo_binout): $(src_path)geo/test.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(geo_arout): $(geo_objout)
	$(AR) $(ar_out)$@ $^
	cp $(src_path)geo/geo.h $(inc_path)

$(geo_objout): $(src_path)geo/geo.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(bin_out)$@ 

$(geo_libout): $(src_path)geo/geo.c
	$(CC) $(CFLAGS) -DSHARED=0 $(INC) $(nm_pic_opt) $(nm_shared_opt) $^ $(bin_out)$@
	cp $(src_path)geo/geo.h $(inc_path)
	

## math

ifeq ($(CC_NAME), msvc)
math_lib_path := PATH
math_ldflags =
LDLIBS = $(lib_path)libgeo$(ar_ext)
else
math_lib_path := LD_LIBRARY_PATH
math_ldflags = $(LDFLAGS)
LDLIBS = -lgeo
endif


math: math_static math_shared
math_test: math_static_test math_shared_test


math_static_binout := $(bin_path)math_static$(bin_ext)

math_static: $(math_static_binout)
math_static_test: math_static
	$(math_static_binout)

$(math_static_binout): $(src_path)math/math1.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


math_shared_binout := $(bin_path)math_shared$(bin_ext)

math_shared: geo_shared $(math_shared_binout)
math_shared_test: math_shared
	$(math_lib_path)=$(lib_path) $(math_shared_binout)

$(math_shared_binout): $(src_path)math/math1.c 
	$(CC) $(CFLAGS) -DSHARED=1 $(INC) $(math_ldflags) $^ $(bin_out)$@ $(LDLIBS) 

