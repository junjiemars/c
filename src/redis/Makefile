# ./configure --has-redis


redis_out := $(CURDIR)/$(out)/var/redis

redis_git_src := 'https://github.com/redis/redis.git'
redis_home := $(redis_root)/redis_home

redis: redis_core																\
       redis_module_hello

redis_test: redis_core_test											\
            redis_module_hello_test


# env
redis_cc_opt :=
redis_ld_opt :=


ifeq (1, $(_MEMORY_))
redis_cc_opt += $(f_sanitize)
redis_ld_opt += $(f_sanitize)
endif # end of _MEMORY_



$(redis_home):
	git clone --depth=1 --branch=unstable $(redis_git_src) $@


# core
redis_core_root := $(CURDIR)/$(redis_root)/core
redis_core_prefix := $(redis_out)/core
redis_core_binout := $(redis_core_prefix)/bin/redis-server
redis_core_cli := $(redis_core_prefix)/bin/redis-cli


ifeq (msvc, $(CC_NAME))
redis_core:
	@echo "#skip redis_core_test ..."
redis_core_test: redis_core
else
redis_core: $(redis_core_binout)
redis_core_test: redis_core
	$(redis_core_binout) $(redis_core_prefix)/redis.conf
	sleep 3
	$(redis_core_cli) set x 123
	$(redis_core_cli) get x
	$(redis_core_cli) shutdown
endif # end of msvc


$(redis_core_binout): $(redis_home)									\
                      $(redis_core_root)/redis.conf
	cd $(redis_home)															\
		&& make PREFIX="$(redis_core_prefix)"				\
            MALLOC=libc													\
            OPTIMIZATION=$(nm_optimize_opt)			\
            CFLAGS="$(redis_cc_opt)"						\
            LDFLAGS="$(redis_ld_opt)"						\
    install																			\
    && cp $(redis_core_root)/redis.conf					\
					$(redis_core_prefix)/redis.conf


# hello
redis_hello_inc := $(INC) $(nm_inc_opt)$(redis_home)/src
redis_hello_cflags := $(CFLAGS) $(f_no_common) $(f_pic) $(nm_shared_opt)
redis_hello_module_root := $(CURDIR)/$(redis_root)/hello
redis_module_hello_prefix := $(redis_out)/hello
redis_module_hello_svr := $(redis_module_hello_prefix)/bin/redis-server
redis_module_hello_cli := $(redis_module_hello_prefix)/bin/redis-cli
redis_module_hello_binout := $(redis_module_hello_prefix)/bin/hello$(lib_ext)


ifeq (msvc, $(CC_NAME))
redis_module_hello:
	@echo "#skip redis_module_hello_test ..."
redis_module_hello_test: redis_module_hello
else
redis_module_hello: $(redis_module_hello_binout)
redis_module_hello_test: redis_module_hello
	$(redis_module_hello_svr) $(redis_module_hello_prefix)/redis.conf
	sleep 3
	$(redis_module_hello_cli) HELLO
	$(redis_module_hello_cli) shutdown
endif # end of msvc

$(redis_module_hello_binout): $(redis_root)/hello/hello.c	\
                              $(redis_module_hello_svr)
	$(CC) $(redis_hello_cflags) $(redis_hello_inc) $< $(bin_out)$@

$(redis_module_hello_svr): $(redis_home)													\
                           $(redis_hello_module_root)/redis.conf
	cd $(redis_home)																				\
		&& make PREFIX="$(redis_module_hello_prefix)"					\
            MALLOC=libc																		\
            CFLAGS="$(redis_cc_opt)"											\
            LDFLAGS="$(redis_ld_opt)"											\
    install																								\
    && cp $(redis_hello_module_root)/redis.conf						\
					$(redis_module_hello_prefix)/redis.conf 				\
    && echo "loadmodule $(redis_module_hello_binout)" >> 	\
            $(redis_module_hello_prefix)/redis.conf 


# clean
redis_clean: clean															\
             clean_redis_home

clean_redis_home:
	-$(RM) -rf $(redis_home)

clean_redis_out:
	test ! -f $(CURDIR)/$(redis_home)/Makefile		\
		|| make -C $(CURDIR)/$(redis_home) clean



.PHONY: redis_clean clean_redis_home clean_redis_out	\
        redis_module_hello redis_module_hello_test


# eof
