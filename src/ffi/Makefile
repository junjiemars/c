# -*- mode:makefile-gmake -*-
#
# ./configure --has-ffi
#


ffi: ffi_jni                                    \
     ffi_nodejs                                 \
     ffi_python

ffi_test: ffi_jni_test                          \
          ffi_nodejs_test                       \
          ffi_python_test



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
ffi_jni: $(jni_square_libout) \
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



# python
python_venv_dir := $(CURDIR)/$(ffi_root)/python/venv
python_inc := $(python_inc)
python_cflags := $(python_cflags) $(nm_optimize_opt) $(nm_symbol_opt)
python_ldflags := $(python_ldflags)

ffi_python_venv := $(python_venv_dir)/bin/activate
ffi_python_required := $(python_venv_dir)/bin/pip
ffi_python_c_cflags := $(python_cflags) $(nm_inc_opt)$(CURDIR)/$(out)
ffi_python_c_binout := $(ffi_root)/python/c/nore.cpython-$(python_mod_id).so \
                       $(ffi_root)/python/c/nore.egg-info
ffi_python_c_tgzout := $(tmp_path)/nore*.tar.gz
ffi_python_driver_binout := $(bin_path)/$(ffi_prefix)_python_c_driver$(bin_ext)

ifeq ($(has_python),yes)
ffi_python: ffi_python_c ffi_python_driver
ffi_python_test: ffi_python_test
else
ffi_python:
	@echo "# skip $@, no python env found"
ffi_python_test: ffi_python
	@echo "# skip $@, no python env found"
endif

$(ffi_python_venv_required): $(ffi_python_venv)
	@source $< && pip install --upgrade pip setuptools build
$(ffi_python_venv):
	@python -mvenv $(python_venv_dir)

ffi_python_c: $(ffi_python_venv_required) \
              $(ffi_python_c_binout)

ffi_python_driver: $(ffi_python_driver_binout)

ffi_python_c_test: ffi_python_c
	@source $(ffi_python_venv) && python -c'import nore;print("2*3=%d"%(nore.multiply(2,3)))'
ffi_python_c_clean:
	test -z "$(ffi_python_c_binout)" || rm -rf $(ffi_python_c_binout)
ffi_python_c_dist: $(ffi_python_venv_required) \
                   $(ffi_python_c_tgzout)
$(ffi_python_c_binout): $(ffi_python_venv) \
                        $(ffi_root)/python/c/foo.c
	CFLAGS="$(python_cflags)" source $< \
    && pip install -v --editable $(ffi_root)/python/c
$(ffi_python_c_tgzout): $(ffi_python_venv) \
                        $(ffi_root)/python/c/foo.c
	CFLAGS="$(python_cflags) $(ffi_python_c_inc)" && source $< \
    && python -m build -v -o $(tmp_path) $(ffi_root)/python/c

$(ffi_python_driver_binout): $(ffi_root)/python/c/d1.c
	$(CC) $(python_cflags) $(python_inc) $(python_ldflags) $(bin_out)$@ $^


.PHONY: ffi_jni ffi_jni_test \
        ffi_nodejs ffi_nodejs_test \
        ffi_python ffi_python_test

# eof
