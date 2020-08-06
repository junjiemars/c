#
# ./configure --has-ffi
#

INC += -I$(ffi_root)

ffi: jni
ffi_test: jni_test

ifeq ($(javac_ge_8),$(javac_ver))
# jni
square_libout := $(lib_path)libsquare$(lib_ext)
jni_classpath += -classpath .$(nm_p)$(bin_path)

jni: $(square_libout)
jni_test: jni
	$(JAVA) $(jni_classpath) -Djava.library.path=$(lib_path) Java2c

jni_inc += $(INC) $(jni_ldflags)
jni_cflags += $(CFLAGS) $(nm_shared_opt)

java2c_h := $(inc_path)Java2c.h
java2c_classout := $(bin_path)Java2c.class

# square_libout does not need link with -ljvm
$(square_libout): $(java2c_h) $(ffi_root)jni/square.c
	$(CC) $(jni_cflags) $(jni_inc) $(ffi_root)jni/square.c $(bin_out)$@ 

$(java2c_h): $(ffi_root)jni/Java2c.java
	$(JAVAH) -h $(inc_path) -d $(bin_path) $(ffi_root)jni/Java2c.java

else
jni:
jni_test:
endif
# eof
