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

hello_module_root := $(CURDIR)/src/nginx/hello

configure: $(nd_sh) $(nginx_home_auto)
	$(nd_sh) --home=$(nginx_home)                  \
           --target=http                         \
           --chain=$(chain)                      \
           --gen-shell=yes                       \
           --opt-add-module=$(hello_module_root) \
           --opt-debug=$(opt_debug)              \
           make configure

make: $(nd_sh) $(nginx_home_auto)
	$(nd_sh) --home=$(nginx_home)                  \
           --target=http                         \
           --chain=$(chain)                      \
           --gen-shell=yes                       \
           --opt-add-module=$(hello_module_root) \
           --opt-debug=$(opt_debug)              \
           make make

.PHONY: configure make
