# ./configure --has-nginx


nginx_out := $(CURDIR)/$(out)

nginx_git_src := 'https://github.com/nginx/nginx.git'
nginx_home := $(nginx_root)/nginx_home
nginx_configure := $(nginx_home)/auto/configure


nginx: nginx_module_hello

nginx_test: nginx_module_hello_test


nginx_cc_opt := $(nm_optimize_opt)
nginx_ld_opt :=

ifeq ($(_MEMORY_),1)
nginx_cc_opt += $(f_sanitize) -DNGX_DEBUG_PALLOC=1
nginx_ld_opt += $(f_sanitize)
endif # end of _MEMORY_


$(nginx_home):
	git clone --depth=1 --branch=master $(nginx_git_src) $@


# hello
hello_module_root := $(CURDIR)/$(nginx_root)/hello
nginx_module_hello_prefix := $(nginx_out)/var/hello
nginx_module_hello_binout := $(nginx_module_hello_prefix)/sbin/nginx

nginx_module_hello: $(nginx_module_hello_binout)
nginx_module_hello_test: nginx_module_hello
	$(nginx_module_hello_binout) -T

$(nginx_module_hello_binout): $(nginx_home)
	cd $(nginx_home)																						\
		&& auto/configure --prefix=$(nginx_module_hello_prefix)		\
                      --without-http_fastcgi_module						\
                      --without-http_uwsgi_module							\
                      --without-http_scgi_module							\
                      --without-http_memcached_module					\
                      --without-http_rewrite_module						\
                      --without-http-cache										\
                      --without-pcre													\
                      --add-module=$(hello_module_root)				\
                      --with-cc-opt="$(nginx_cc_opt)"					\
                      --with-ld-opt="$(nginx_ld_opt)"					\
                      --with-debug														\
    && make -j4 install																				\
    && cp $(hello_module_root)/nginx.conf								\
					$(nginx_module_hello_prefix)/conf/nginx.conf


# clean
nginx_clean: clean_nginx_home										\
             clean_nginx_out

clean_nginx_home:
	-$(RM) -rf $(nginx_home)

clean_nginx_out: clean
	-$(RM) -r $(out)/*_temp
	-$(RM) -r $(out)/html
	-$(RM) -r $(out)/logs
	-$(RM) -r $(out)/conf



.PHONY: nginx_clean clean_nginx_home clean_nginx_out

# eof

