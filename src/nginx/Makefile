# ./configure --has-nginx


nginx_out := $(CURDIR)/$(out)

nginx_git_src := 'https://github.com/nginx/nginx.git'
nginx_home := $(nginx_root)/nginx_home
nginx_configure := $(nginx_home)/auto/configure

hello_module_root := $(CURDIR)/$(nginx_root)/hello
nginx_module_hello_binout := $(nginx_out)/bin/nginx


nginx: nginx_module_hello

nginx_test: nginx_module_hello_test



# hello
nginx_module_hello: $(nginx_module_hello_binout)
nginx_module_hello_test: nginx_module_hello
	$(nginx_module_hello_binout) -T

$(nginx_module_hello_binout): $(nginx_home)
	cd $(nginx_home)																															\
		&& auto/configure --prefix=$(nginx_out)																			\
                      --sbin-path=$(nginx_out)/bin															\
                      --without-http_fastcgi_module															\
                      --without-http_uwsgi_module																\
                      --without-http_scgi_module																\
                      --without-http_memcached_module														\
                      --without-http_rewrite_module															\
                      --without-http-cache																			\
                      --without-pcre																						\
                      --add-module=$(hello_module_root)													\
                      --with-cc-opt=-O0																					\
                      --with-debug																							\
    && make -j4 install																													\
    && cp $(hello_module_root)/nginx.conf $(nginx_out)/conf/nginx.conf


$(nginx_home):
	git clone --depth=1 --branch=master $(nginx_git_src) $@


# clean
nginx_clean: clean_nginx_home

clean_nginx_home: $(nginx_home)
	rm -r $(nginx_home)



.PHONY: nginx_clean nginx_priori

# eof

