

geo: $(lib_path)libgeo.so


geo_cflags := $(CFLAGS) $(CL_PIC_OPT) $(CL_INCS) -I$(src_path)
geo_ldflags := $(LDFLAGS)

$(tmp_path)geo.o: $(src_path)geo.c 
	$(CC) $(geo_cflags) -c $^ -o $@
	cp $(src_path)geo.h $(inc_path)

$(lib_path)libgeo.so: $(tmp_path)geo.o
	$(LINK) $(geo_ldflags) $^ -o $@
