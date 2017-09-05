
ffi: jni
ffi_test: jni_test

INC += -I$(ffi_root)


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

# square_libout does not need link with -ljvm
$(square_libout): $(square_h) $(ffi_root)jni/square.c
	$(CC) $(jni_cflags) $(jni_inc) $(ffi_root)jni/square.c $(bin_out)$@ 

$(square_h): $(java2c_classout)
	$(JAVAH) $(jni_binout) $@ -cp $(jni_classpath) Java2c

$(java2c_classout): $(ffi_root)jni/Java2c.java
	$(JAVAC) $(jni_symbol) -d $(bin_path) $^

