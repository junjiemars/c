#
# ./configure --has-ffi
#


ffi: ffi_jni                                    \
     ffi_nodejs

ffi_test: ffi_jni_test                          \
          ffi_nodejs_test


# env
ffi_prefix := ffi

INC += $(nm_inc_opt)$(ffi_root) $(nm_inc_opt)$(root)/posix


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
	$(JAVAH) $(inc_path) -d $(bin_path) $^


ifeq (YES, $(has_java))
ffi_jni: $(jni_square_libout)										\
         $(java2c_classout)
ffi_jni_test: ffi_jni
	$(JAVA) $(jni_classpath) -Djava.library.path=$(lib_path) Java2c
else
ffi_jni:
	@echo "#skip ffi_jni_test ..."
ffi_jni_test: ffi_jni
endif


# node.js
ffi_nodejs_prefix := $(CURDIR)/$(out)/var/nodejs
ffi_nodejs_libm_js := $(CURDIR)/$(ffi_root)/node/n.js
ffi_nodejs := $(ffi_nodejs_prefix)/package-lock.json

ifeq (YES, $(has_nodejs))
$(ffi_nodejs):
	@echo "----------"
	@echo "npm install --prefix=$(ffi_nodejs_prefix) ffi-napi ..."
	-@npm list --silent --prefix=$(ffi_nodejs_prefix) ffi-napi >/dev/null	\
		|| npm install --silent --prefix=$(ffi_nodejs_prefix) ffi-napi
ffi_nodejs_test: $(ffi_nodejs)
	NODE_PATH=$(ffi_nodejs_prefix)/node_modules node $(ffi_nodejs_libm_js)
else
ffi_nodejs:
	@echo "#skip ffi_nodejs_test ..."
ffi_nodejs_test: ffi_nodejs
endif

$(ffi_nodejs_prefix):
	$(MD) -p $@



.PHONY: ffi_jni ffi_jni_test										\
        ffi_nodejs ffi_nodejs_test

# eof
