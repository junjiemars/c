# ./configure --has-nginx

# check or download nd.sh
nd_sh_src := 'https://raw.githubusercontent.com/junjiemars/kit/master/ul/nd.sh'
nd_sh := $(CURDIR)/src/nginx/nd.sh
$(nd_sh):
	curl -sqL -o $@ $(nd_sh_src) && chmod u+x $@

nginx_home := $(CURDIR)/src/nginx/nginx_home

opt_debug :=
ifeq ($(NM_DEBUG),YES)
opt_debug := yes
endif

nginx_prefix := $(CURDIR)/$(tmp_path)
hello_module_root := $(CURDIR)/src/nginx/hello

$(nginx_home)/Makefile: $(nd_sh)
	$(nd_sh) --home=$(nginx_home)                   \
           --prefix=$(nginx_prefix)               \
           --target=http                          \
           --gen-shell=no                         \
           --opt-add-module=$(hello_module_root)  \
           --opt-debug=$(opt_debug)               \
           make configure												  

$(nginx_home)/objs/nginx: $(nginx_home)/Makefile
	$(nd_sh) --home=$(nginx_home)                   \
           --prefix=$(nginx_prefix)               \
           --target=http                          \
           --gen-shell=no                         \
           --opt-add-module=$(hello_module_root)  \
           --opt-debug=$(opt_debug)               \
           make make

nginx_module_hello_binout := $(tmp_path)sbin/nginx

$(nginx_module_hello_binout): $(nginx_home)/objs/nginx
	$(nd_sh) --home=$(nginx_home)                   \
           --prefix=$(nginx_prefix)               \
           --target=http                          \
           --gen-dir=$(CURDIR)/$(nginx_root)      \
           --gen-shell=yes                        \
           --opt-add-module=$(hello_module_root)  \
           --opt-debug=$(opt_debug)               \
           make install
	cp $(nginx_root)/hello/nginx.conf $(tmp_path)conf/nginx.conf

clean_nginx: $(nd_sh)
	make -C $(nginx_home) clean


nginx_module_hello: $(nginx_module_hello_binout)
nginx_module_hello_test: nginx_module_hello
	$(nginx_module_hello_binout) -t

