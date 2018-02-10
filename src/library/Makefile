
library: geo math_static math_shared
library_test: geo_test math_static_test math_shared_test


INC += -I$(library_root)


# geo
geo_arout := $(lib_path)geo$(ar_ext)
geo_binout := $(tmp_path)geo$(bin_ext)
geo_objout := $(tmp_path)geo$(obj_ext)
geo_libout := $(lib_path)libgeo$(lib_ext)
geo_h := $(inc_path)geo.h

geo: $(geo_binout)
geo_test: geo
	$(geo_binout)

$(geo_binout): $(library_root)geo/test.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(geo_arout): $(geo_objout) $(geo_h)
	$(AR) $(ARFLAGS) $(ar_out)$@ $<

$(geo_objout): $(library_root)geo/geo.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(bin_out)$@ 

$(geo_libout): $(library_root)geo/geo.c $(geo_h)
	$(CC) $(CFLAGS) -DSHARED=0 $(INC) $(nm_pic_opt) $(nm_shared_opt) $< $(bin_out)$@
	
$(geo_h): $(library_root)geo/geo.h
	cp $< $(inc_path)


## math

ifeq ($(CC_NAME), msvc)
math_lib_path := PATH
math_ldflags =
ld_geo_lib = $(lib_path)libgeo$(ar_ext)
else
math_lib_path := LD_LIBRARY_PATH
math_ldflags = $(LDFLAGS)
ld_geo_lib = -lgeo
endif

math_static_binout := $(bin_path)math_static$(bin_ext)
math_shared_binout := $(bin_path)math_shared$(bin_ext)

math_static: $(math_static_binout)
math_shared: $(math_shared_binout)
math_static_test: math_static
	$(math_static_binout)
math_shared_test: math_shared
	$(math_lib_path)=$(lib_path) $(math_shared_binout)

$(math_static_binout): $(library_root)math/math1.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDLIBS)

$(math_shared_binout): $(library_root)math/math1.c $(geo_libout)
	$(CC) $(CFLAGS) -DSHARED=1 $(INC) $(math_ldflags) $< $(bin_out)$@ $(ld_geo_lib) 


.PHONY: geo geo_test math_static math_static_test math_shared math_shared_test
