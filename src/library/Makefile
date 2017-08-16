
# default is static

library: geo math
library_test: geo_test math_test

# make CFLAGS=-DSHARED=1 -f objs/Makefile library_shared_test
library_shared: geo_shared math_shared
library_shared_test: math_shared_test


INC += -I$(src_path)

# geo
geo_arout := $(lib_path)geo$(ar_ext)
geo_binout := $(tmp_path)geo$(bin_ext)
geo_objout := $(tmp_path)geo$(obj_ext)

geo: $(geo_arout)
geo_test: geo $(geo_binout)
	$(geo_binout)

$(geo_binout): $(src_path)geo/geo.c $(src_path)geo/test.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(geo_arout): $(geo_objout)
	$(AR) $(ar_out)$@ $^
	cp $(src_path)geo/geo.h $(inc_path)

$(geo_objout): $(src_path)geo/geo.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(bin_out)$@ 

# math
math_binout := $(bin_path)math$(bin_ext)

math: $(math_binout)
math_test: math
	$(math_binout)

$(math_binout): $(src_path)math/math1.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

# geo shared
geo_libout := $(lib_path)libgeo$(lib_ext)

geo_shared: $(geo_libout)
	
$(geo_libout): $(src_path)geo/geo.c
	$(CC) $(CFLAGS) -DSHARED=1 $(INC) $(nm_pic_opt) $(nm_shared_opt) $^ $(bin_out)$@
	cp $(src_path)geo/geo.h $(inc_path)

# math shared

ifeq ($(CC_NAME), msvc)
math_lib_path := PATH
math_ldflags =
LDLIBS = $(lib_path)libgeo.lib
else
math_lib_path := LD_LIBRARY_PATH
math_ldflags = $(LDFLAGS)
LDLIBS = -lgeo
endif

math_shared_binout := $(bin_path)math_shared$(bin_ext)

math_shared: geo_shared $(math_shared_binout)
math_shared_test: math_shared
	$(math_lib_path)=$(lib_path) $(math_shared_binout)

$(math_shared_binout): $(src_path)math/math1.c 
	$(CC) $(CFLAGS) $(INC) $(math_ldflags) $^ $(bin_out)$@ $(LDLIBS) 

