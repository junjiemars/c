
ffi: jni
ffi_test: jni_test

INC += -I$(src_path)


# jni
square_libout := $(lib_path)libsquare$(lib_ext)
jni_classpath += .$(nm_p)$(bin_path)

jni: $(square_libout)
jni_test: jni
	$(JAVA) -cp $(jni_classpath) -Djava.library.path=$(lib_path) Java2c

jni_inc += $(INC) $(jni_ldflags)
jni_cflags += $(CFLAGS) $(nm_pic_opt) $(nm_shared_opt)

square_h := $(inc_path)square.h
java2c_classout := $(bin_path)Java2c.class

$(square_libout): $(square_h) $(src_path)jni/square.c
	$(CC) $(jni_cflags) $(jni_inc) $(src_path)jni/square.c $(bin_out)$@ $(jni_libs)

$(square_h): $(java2c_classout)
	$(JAVAH) $(jni_binout) $@ -cp $(jni_classpath) Java2c

$(java2c_classout): $(src_path)jni/Java2c.java
	$(JAVAC) $(jni_symbol) -d $(bin_path) $^

