#
# ./configure --has-cxx
#
#

ifeq ($(has_cmake),)
cxx:
	@echo "#skip ..."
cxx_test:
	@echo "#skip ..."
else

cxx:                                             \
    cxx_std14

cxx_test:                                        \
         cxx_std14_test

endif


# env
ifeq ($(NM_OPTIMIZE),NO)
CMAKE_CXX_FLAGS += $(nm_symbol_opt)
endif

cxx_build_root := $(tmp_path)/cxx

# std14
cxx_std14_build := $(cxx_build_root)/std14
cxx_std14_binout := $(cxx_std14_build)/cxx_std14

cxx_std14_init: $(cxx_root)/std14/CMakeLists.txt
	cmake -S $(cxx_root)/std14 -B $(cxx_std14_build)

cxx_std14: cxx_std14_init
	make -C $(cxx_std14_build)

cxx_std14_test: cxx_std14
	-$(cxx_std14_binout)

# eof
