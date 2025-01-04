# -*- mode:makefile-gmake -*-
#
# ./configure --has-library
#

library: geo                                    \
         math_static                            \
         math_shared

library_test: geo_test                          \
              math_static_test									\
              math_shared_test



# env
INC += -I$(library_root)



# geo
geo_arout := $(lib_path)/geo$(ar_ext)
geo_binout := $(bin_path)/geo$(bin_ext)
geo_objout := $(tmp_path)/geo$(obj_ext)
geo_libout := $(lib_path)/libgeo$(lib_ext)
geo_h := $(inc_path)/geo.h

geo: $(geo_binout)
geo_test: geo
	$(geo_binout)
geo_list_ar: $(geo_arout)
	nm $<

$(geo_binout): $(library_root)/geo/test.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^

$(geo_arout): $(geo_objout) $(geo_h)
	$(AR) $(ARFLAGS) $(ar_out)$@ $<

$(geo_objout): $(library_root)/geo/geo.c
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $(nm_stage_c) $^

$(geo_libout): $(library_root)/geo/geo.c $(geo_h)
	$(CC) $(CFLAGS) -DSHARED=0 $(INC) $(nm_shared_opt) $(bin_out)$@ $<

$(geo_h): $(library_root)/geo/geo.h
	cp $< $(inc_path)



# math
stdmath_lib :=
ifeq (msvc, $(CC_NAME))
LD_LIBRARY_PATH := PATH
LDLIBS := libgeo$(ar_ext)
stdmath_lib := $(nm_link_opt) msvcrt.lib
endif

ifeq (Linux, $(NM_SYSTEM))
LD_LIBRARY_PATH := LD_LIBRARY_PATH
LDLIBS := $(nm_lib_opt)geo
stdmath_lib := $(nm_lib_opt)m
endif

ifeq (Darwin, $(NM_SYSTEM))
LD_LIBRARY_PATH := DYLD_LIBRARY_PATH
LDLIBS := $(nm_lib_opt)geo
endif



math_static_binout := $(bin_path)/math_static$(bin_ext)
math_shared_binout := $(bin_path)/math_shared$(bin_ext)

math_static: $(math_static_binout)
math_shared: $(math_shared_binout)

math_static_test: math_static
	$(math_static_binout)

ifeq (NO, $(ld_rpath_opt))
math_shared_test: math_shared
	$(LD_LIBRARY_PATH)=$(lib_path) $(math_shared_binout)
else
math_shared_test: math_shared
	$(math_shared_binout)
endif

$(math_static_binout): $(library_root)/math/math1.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $(bin_out)$@ $^ $(stdmath_lib)

$(math_shared_binout): $(library_root)/math/math1.c $(geo_libout)
	$(CC) $(CFLAGS) -DSHARED=1 $(INC) $(bin_out)$@ $< $(LDFLAGS) $(LDLIBS)



.PHONY: geo geo_test geo_list_ar                \
        math_static math_static_test            \
        math_shared math_shared_test

# eof
