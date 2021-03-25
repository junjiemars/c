#
# ./configure --has-ffi
#

ffi_prefix := ffi
INC += -I$(ffi_root)

ffi: ffi_jni
ffi_test: ffi_jni_test

# jni
jni_square_libout := $(lib_path)/libsquare$(lib_ext)
jni_classpath := -classpath .$(nm_path_sep)$(bin_path)

jni_inc += $(INC)
jni_cflags += $(CFLAGS) $(nm_shared_opt)

java2c_h := $(inc_path)/Java2c.h
java2c_classout := $(bin_path)/Java2c.class

$(jni_square_libout): $(java2c_h)								\
                      $(ffi_root)/jni/square.c
	$(CC) $(jni_cflags) $(jni_inc) $(ffi_root)/jni/square.c $(bin_out)$@

$(java2c_h) $(java2c_classout): $(ffi_root)/jni/Java2c.java
	$(JAVAC) -h $(inc_path) -d $(bin_path) $^

ifeq (YES, $(javac_ge_8))
ffi_jni: $(jni_square_libout)										\
         $(java2c_classout)
ffi_jni_test: ffi_jni
	$(JAVA) $(jni_classpath) -Djava.library.path=$(lib_path) Java2c
else
ffi_jni:
	@echo "#skip ffi_jni_test, need java8."
ffi_jni_test: ffi_jni
endif

.PHONY: ffi_jni ffi_jni_test

# eof
