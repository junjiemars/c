#
# ./configure --has-library
#


library: cffix																	\
         geo																		\
         math_static														\
         math_shared

library_test: cffix_test												\
              geo_test													\
              math_static_test									\
              math_shared_test


# env
INC += -I$(library_root)


# cffix
cffix_libout := $(lib_path)/libcffix$(lib_ext)
cffix_h := $(inc_path)/cffix.h
cffix_binout := $(bin_path)/cffix_call$(bin_ext)

cffix_ldlibs :=
cffix_lib_path := $(lib_path)
ifeq (msvc, $(CC_NAME))
	LD_LIBRARY_PATH := PATH
	cffix_ldlibs := libcffix$(ar_ext)
else
	cffix_ldlibs := $(nm_lib_opt)cffix
	LD_LIBRARY_PATH := LD_LIBRARY_PATH
	ifeq (rpath, $(nm_link_opt))
		cffix_lib_path :=
	endif													# rpath
endif														# msvc


cffix: $(cffix_libout) $(cffix_binout)
cffix_test: cffix
	$(LD_LIBRARY_PATH)=$(cffix_lib_path) $(cffix_binout) "120, 0123456789"


$(cffix_libout): $(library_root)/cffi/cffix.c $(cffix.h)
	$(CC) $(CFLAGS) -DSHARED=1 $(INC) $(nm_shared_opt) $< $(bin_out)$@

$(cffix_h): $(library_root)/cffi/cffix.h
	cp $< $(inc_path)

$(cffix_binout): $(library_root)/cffi/call.c $(cffix_libout)
	$(CC) $(CFLAGS) -DSHARED=0 $(INC) $< $(bin_out)$@ $(LDFLAGS) $(cffix_ldlibs)


# geo
geo_arout := $(lib_path)/geo$(ar_ext)
geo_binout := $(bin_path)/geo$(bin_ext)
geo_objout := $(tmp_path)/geo$(obj_ext)
geo_libout := $(lib_path)/libgeo$(lib_ext)
geo_h := $(inc_path)/geo.h

geo: $(geo_binout)
geo_test: geo
	$(geo_binout)

$(geo_binout): $(library_root)/geo/test.c $(geo_arout)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(geo_arout): $(geo_objout) $(geo_h)
	$(AR) $(ARFLAGS) $(ar_out)$@ $<

$(geo_objout): $(library_root)/geo/geo.c
	$(CC) $(CFLAGS) $(INC) $(nm_stage_c) $^ $(bin_out)$@ 

$(geo_libout): $(library_root)/geo/geo.c $(geo_h)
	$(CC) $(CFLAGS) -DSHARED=0 $(INC) $(nm_shared_opt) $< $(bin_out)$@

$(geo_h): $(library_root)/geo/geo.h
	cp $< $(inc_path)


# math
stdmath_lib :=
geo_lib_path := $(lib_path)
ifeq (msvc, $(CC_NAME))
	LD_LIBRARY_PATH := PATH
	LDLIBS := libgeo$(ar_ext)
else
	LD_LIBRARY_PATH := LD_LIBRARY_PATH
	LDLIBS := $(nm_lib_opt)geo
	ifeq (Linux, $(NM_SYSTEM))
		stdmath_lib := $(nm_lib_opt)m
		LDLIBS += $(stdmath_lib)
	endif 												# Linux
	ifeq (rpath, $(nm_link_opt))
		geo_lib_path :=
	endif													# rpath
endif														# msvc

math_static_binout := $(bin_path)/math_static$(bin_ext)
math_shared_binout := $(bin_path)/math_shared$(bin_ext)

math_static: $(math_static_binout)
math_shared: $(math_shared_binout)
math_static_test: math_static
	$(math_static_binout)
math_shared_test: math_shared
	$(LD_LIBRARY_PATH)=$(geo_lib_path) $(math_shared_binout)

$(math_static_binout): $(library_root)/math/math1.c $(geo_arout) $(stdmath_lib)
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(math_shared_binout): $(library_root)/math/math1.c $(geo_libout)
	$(CC) $(CFLAGS) -DSHARED=1 $(INC) $< $(bin_out)$@ $(LDFLAGS) $(LDLIBS)


.PHONY: geo geo_test														\
        math_static math_static_test						\
        math_shared math_shared_test

# eof
