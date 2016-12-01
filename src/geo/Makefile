

geo_binout := $(lib_path)libgeo$(mod_ext)

geo: $(geo_binout)

geo_cflags := $(CFLAGS) $(NM_PIC_OPT) $(INC) -I$(src_path)
geo_ldflags := $(LDFLAGS) 


$(tmp_path)geo$(obj_ext): $(src_path)geo.c 
	$(CC) $(geo_cflags) -c $^ $(obj_out)$@
	cp $(src_path)geo.h $(inc_path)

$(geo_binout): $(tmp_path)geo$(obj_ext)
	$(CC) $(CFLAGS) $(geo_ldflags) $^ $(bin_out)$@
