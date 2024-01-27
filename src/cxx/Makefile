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
cxx_compile_commands := compile_commands.json

# std14
cxx_std14_build := $(cxx_build_root)/std14
cxx_std14_binout := $(cxx_std14_build)/cxx_std14
cxx_std14_makefile := $(cxx_build_build)/Makefile
cxx_std14_compile_commands := $(cxx_std14_build)/$(cxx_compile_commands)

cxx_std14: $(cxx_std14_makefile) \
           $(cxx_std14_binout)
cxx_std14_test: cxx_std14
	-$(cxx_std14_binout)
cxx_std14_clean:
	make -C $(cxx_std14_build) clean
$(cxx_std14_makefile): $(cxx_root)/std14/CMakeLists.txt
	cmake -S $(cxx_root)/std14 -B $(cxx_std14_build) \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
		&& cp $(cxx_std14_compile_commands) $(cxx_root)/std14/

$(cxx_std14_binout): $(cxx_root)/std14/main.cpp
	make -C $(cxx_std14_build) cxx_std14

# eof
