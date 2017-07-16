

geo_libout := $(lib_path)libgeo$(lib_ext)
geo_binout := $(tmp_path)geo$(bin_ext)

geo: $(geo_libout)
geo_test: $(geo_binout)
	$(geo_binout)

geo_cflags := $(CFLAGS) $(nm_pic_opt) $(INC) -I$(src_path)
geo_ldflags := $(LDFLAGS) $(nm_shared_opt)


$(tmp_path)geo$(obj_ext): $(src_path)geo.c 
	$(CC) $(geo_cflags) -c $^ $(obj_out)$@
	cp $(src_path)geo.h $(inc_path)

$(geo_libout): $(tmp_path)geo$(obj_ext)
	$(CC) $(CFLAGS) $(geo_ldflags) $^ $(bin_out)$@

$(geo_binout): $(src_path)geo.c $(src_path)test.c
	$(CC) $(geo_cflags) $^ $(bin_out)$@
