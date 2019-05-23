# ./configure --has-nginx

# check or download nd.sh
ND := nd.sh
# check or download nginx source from github
NGINX_ROOT := /opt/open/nginx

hello_module_root := $(CURDIR)/src/nginx/hello

configure:
	$(ND) --home=$(NGINX_ROOT)                  \
        --target=http                         \
        --chain=yes                           \
        --gen-shell=yes                       \
        --opt-add-module=$(hello_module_root) \
        make configure

make:
	$(ND) --home=$(NGINX_ROOT)                  \
        --target=http                         \
        --chain=yes                           \
        --gen-shell=yes                       \
        --opt-add-module=$(hello_module_root) \
        make make

.PHONY: configure make
