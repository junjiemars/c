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
python_venv_activate := $(python_venv_dir)/bin/activate
python_venv_required := $(python_venv_dir)/bin/pip
python_inc := $(python_inc)
python_cflags := $(python_cflags)
python_ldflags := $(python_ldflags)

ifeq ($(has_python),yes)
ffi_python: ffi_python_c
ffi_python_test: ffi_python_c_test
else
ffi_python:
	@echo "# skip $@, no Python env found"
ffi_python_test: ffi_python
	@echo "# skip $@, no Python env found"
endif

$(python_venv_required): $(python_venv_activate)
	@source $< && pip install --upgrade pip setuptools build maturin
$(python_venv_activate):
	@python -mvenv $(python_venv_dir)

# Python(C)
ffi_python_c_inc := $(python_inc) $(nm_inc_opt)$(CURDIR)/$(out)
ffi_python_c_cflags := $(python_cflags) $(nm_optimize_opt) $(nm_symbol_opt)
ffi_python_c_cflags := $(python_ldflags)
ffi_python_c_binout := $(ffi_root)/python/c/nore$(python_mod_suffix) $(ffi_root)/python/c/nore.egg-info
ffi_python_c_tgzout := $(tmp_path)/nore*.tar.gz

ifeq ($(has_python_c),yes)
ffi_python_c: $(python_venv_required) $(ffi_python_c_binout)
ffi_python_c_test: ffi_python_c
	@source $(python_venv_activate) && python -c'import nore_c;print("2*3=%d"%(nore_c.multiply(2,3)))'
else
ffi_python_c:
	@echo "# skip $@, no Python(C) env found"
ffi_python_c_test: ffi_python_c
	@echo "# skip $@, no Python(C) env found"
endif

ffi_python_c_clean:
	test -z "$(ffi_python_c_binout)" || rm -rf $(ffi_python_c_binout)
ffi_python_c_dist: $(python_venv_required) $(ffi_python_c_tgzout)
$(ffi_python_c_binout): $(python_venv_activate) $(ffi_root)/python/c/foo.c
	CFLAGS="$(ffi_python_c_cflags)" source $< && pip install -v --editable $(ffi_root)/python/c
$(ffi_python_c_tgzout): $(python_venv_activate) $(ffi_root)/python/c/foo.c
	CFLAGS="$(ffi_python_c_cflags)" && source $< && python -m build -v -o $(tmp_path) $(ffi_root)/python/c

# Python(Rust)
ffi_python_rs_binout := $(ffi_root)/python/rs/target/debug/libnore_rs$(lib_ext)
ffi_python_rs_pyo3 := $(ffi_root)/python/rs/Cargo.toml $(ffi_root)/python/rs/pyproject.toml

ifeq ($(has_python_rs),yes)
ffi_python_rs: $(python_venv_required) $(ffi_python_rs_binout)
ffi_python_rs_test: ffi_python_rs
	@source $(python_venv_activate) && python -c'import nore_rs;print("2*3=%d"%(nore_rs.multiply(2,3)))'
else
ffi_python_rs:
	@echo "# skip $@, no Python(Rust) env found"
ffi_python_rs_test: ffi_python_rs
	@echo "# skip $@, no Python(Rust) env found"
endif

ffi_python_rs_clean:
	cd $(ffi_root)/python/rs && cargo clean
$(ffi_python_rs_binout): $(ffi_python_rs_pyo3) $(ffi_root)/python/rs/src/lib.rs
	cd $(ffi_root)/python/rs && cargo build
	@source $(python_venv_activate) && cd $(ffi_root)/python/rs && maturin develop
$(ffi_python_rs_pyo3): $(python_venv_required)
	@source $(python_venv_activate) && python -m maturin init $(ffi_root)/python/rs -b pyo3
	cd $(ffi_root)/python/rs && cargo add libc



.PHONY: ffi_jni ffi_jni_test \
        ffi_nodejs ffi_nodejs_test \
        ffi_python ffi_python_test

# eof
