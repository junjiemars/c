

geo: $(lib_path)libgeo$(nm_modext)


geo_cflags := $(CFLAGS) $(NM_PIC_OPT) $(NM_INCS) -I$(src_path)
geo_ldflags := $(LDFLAGS) 


$(tmp_path)geo$(nm_objext): $(src_path)geo.c 
	$(CC) $(geo_cflags) -c $^ $(nm_objout)$@
	cp $(src_path)geo.h $(inc_path)

$(lib_path)libgeo$(nm_modext): $(tmp_path)geo$(nm_objext)
	$(CC) $(CFLAGS) $(geo_ldflags) $^ $(nm_binout)$@
