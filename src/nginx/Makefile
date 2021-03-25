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
nginx_hello_module_root := $(CURDIR)/$(nginx_root)/hello
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
                      --without-http_proxy_module							\
                      --without-pcre													\
                      --add-module=$(nginx_hello_module_root)	\
                      --with-cc-opt="$(nginx_cc_opt)"					\
                      --with-ld-opt="$(nginx_ld_opt)"					\
                      --with-debug														\
    && make -j4 install																				\
    && cp $(nginx_hello_module_root)/nginx.conf								\
					$(nginx_module_hello_prefix)/conf/nginx.conf

# njs
nginx_njs_git_src := 'https://github.com/nginx/njs.git'
nginx_njs_module_root := $(CURDIR)/$(nginx_root)/njs

$(nginx_njs_module_root)/src:
	git clone --depth=1 --branch=master $(nginx_njs_git_src) $@


nginx_module_njs_prefix := $(nginx_out)/var/njs
nginx_module_njs_binout := $(nginx_module_njs_prefix)/sbin/nginx

nginx_module_njs: $(nginx_module_njs_binout)
nginx_module_njs_test: nginx_module_njs
	$(nginx_module_njs_binout) -T

$(nginx_module_njs_binout): $(nginx_njs_module_root)/src
	cd $(nginx_home)																										\
		&& auto/configure --prefix=$(nginx_module_njs_prefix)							\
                      --without-http_memcached_module									\
                      --without-http_rewrite_module										\
                      --without-http-cache														\
                      --without-http_proxy_module											\
                      --add-module=$(nginx_njs_module_root)/src/nginx	\
                      --with-cc-opt="$(nginx_cc_opt)"									\
                      --with-ld-opt="$(nginx_ld_opt)"									\
                      --with-debug																		\
    && make -j4 install																								\
    && cp $(nginx_njs_module_root)/nginx.conf													\
					$(nginx_module_njs_prefix)/conf/nginx.conf									\
    && cp $(nginx_njs_module_root)/http.js														\
          $(nginx_module_njs_prefix)/conf/http.js


# clean
nginx_clean: clean_nginx_home										\
             clean_nginx_out

clean_nginx_home:
	-$(RM) -rf $(nginx_home)

clean_nginx_objs:
	test ! -f $(CURDIR)/$(nginx_home)/Makefile		\
		|| make -C $(CURDIR)/$(nginx_home) clean

clean_nginx_out: clean clean_nginx_objs
	-$(RM) -r $(out)/*_temp
	-$(RM) -r $(out)/html
	-$(RM) -r $(out)/logs
	-$(RM) -r $(out)/conf



.PHONY: nginx_clean clean_nginx_home clean_nginx_objs clean_nginx_out	\
        nginx_module_hello nginx_module_hello_test										\
        nginx_module_njs nginx_module_njs_test

# eof
