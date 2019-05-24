# ./configure --has-nginx

# check or download nd.sh
nd_sh_src := 'https://raw.githubusercontent.com/junjiemars/kit/master/ul/nd.sh'
nd_sh := $(CURDIR)/src/nginx/nd.sh
$(nd_sh):
	curl -sqL -o $@ $(nd_sh_src) && chmod u+x $@

# check or download nginx source from github
nginx_src := 'https://github.com/nginx/nginx.git'
nginx_home := $(CURDIR)/src/nginx/nginx_home
nginx_home_auto := $(nginx_home)/auto/configure
$(nginx_home_auto):
	git clone --depth=1 --branch=master $(nginx_src) $(nginx_home)

opt_debug :=
ifeq ($(NM_DEBUG),YES)
opt_debug := yes
endif

nginx_prefix := $(CURDIR)/$(tmp_path)
hello_module_root := $(CURDIR)/src/nginx/hello

configure_nginx: $(nd_sh) $(nginx_home_auto)
	$(nd_sh) --home=$(nginx_home)                   \
           --prefix=$(nginx_prefix)               \
           --target=http                          \
           --chain=$(nginx_chain)                       \
           --gen-shell=no                         \
           --opt-add-module=$(hello_module_root)  \
           --opt-debug=$(opt_debug)               \
           make configure												  

make_nginx: $(nd_sh) $(nginx_home_auto)								  
	$(nd_sh) --home=$(nginx_home)                   \
           --prefix=$(nginx_prefix)               \
           --target=http                          \
           --chain=$(nginx_chain)                       \
           --gen-shell=no                         \
           --opt-add-module=$(hello_module_root)  \
           --opt-debug=$(opt_debug)               \
           make make

install_nginx: $(nd_sh) $(nginx_home_auto)								  
	$(nd_sh) --home=$(nginx_home)                   \
           --prefix=$(nginx_prefix)               \
           --target=http                          \
           --chain=$(nginx_chain)                       \
           --gen-dir=$(CURDIR)/$(nginx_root)      \
           --gen-shell=yes                        \
           --opt-add-module=$(hello_module_root)  \
           --opt-debug=$(opt_debug)               \
           make install
	cp $(nginx_root)/hello/nginx.conf $(CURDIR)/$(nginx_root)

clean_nginx: $(nd_sh) $(nginx_home_auto)
	make -C $(nginx_home) clean

.PHONY: configure_nginx make_nginx install_nginx clean_nginx
