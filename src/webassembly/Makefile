# normal:
# ./configure --has-webassembly 
# emsdk:
# <emsdk_root>/upstream/emscripten/emconfigure ./configure --has-webassembly
# [WASM=1] <emsdk_root>/upstream/emscripten/emmake make -k -C$(CURDIR) clean test
#
# include:
# <script async type="text/javascript" src="wasm_basic.js"></script>
# in html file

webassembly: wasm_basic													\
             wasm_export												\
             wasm_file													\
             wasm_str

webassembly_test: wasm_basic_test								\
                  wasm_export_test							\
                  wasm_file_test								\
                  wasm_str_test


INC += -I$(webassembly_root)
wasm_prefix := wasm
wasm_flags :=
ifeq ($(WASM),1)
	wasm_flags := -s WASM=1
	CFLAGS += -DWASM=1
	bin_ext := .html

	wasm_basic_flags := $(wasm_flags)
	wasm_export_flags := $(wasm_flags)																\
                     -fsanitize=undefined														\
                     -s NO_EXIT_RUNTIME=1														\
                     -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"	\
                     -s SAFE_HEAP=1
  wasm_file_flags := $(wasm_flags)							\
                     -s NO_EXIT_RUNTIME=1       \
                     --preload-file $(webassembly_root)@_wasm_.h@w1.h
	wasm_str_flags := $(wasm_flags)																	\
                    -s NO_EXIT_RUNTIME=1													\
                    -s SAFE_HEAP=1																\
                    -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
endif


# basic

wasm_basic_binout := $(bin_path)$(wasm_prefix)_basic$(bin_ext)

wasm_basic: $(wasm_basic_binout)
ifeq ($(WASM),1)
wasm_basic_test: wasm_basic
	ls -lh $(bin_path)*
else
wasm_basic_test: wasm_basic
	$(wasm_basic_binout)
endif

$(wasm_basic_binout): $(webassembly_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_basic_flags)

# export fn
wasm_export_binout := $(bin_path)$(wasm_prefix)_export$(bin_ext)

wasm_export: $(wasm_export_binout)
ifeq ($(WASM),1)
wasm_export_test: wasm_export
	ls -lh $(bin_path)*
else
wasm_export_test: wasm_export
	$(wasm_export_binout)
endif

$(wasm_export_binout): $(webassembly_root)export/x.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_export_flags)

# file
wasm_file_binout := $(bin_path)$(wasm_prefix)_file$(bin_ext)

wasm_file: $(wasm_file_binout)
ifeq ($(WASM),1)
wasm_file_test: wasm_file
	ls -lh $(bin_path)*
else
wasm_file_test: wasm_file
	$(wasm_file_binout) $(webassembly_root)_wasm_.h
endif

$(wasm_file_binout): $(webassembly_root)file/f.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_file_flags)


# str
wasm_str_binout := $(bin_path)$(wasm_prefix)_str$(bin_ext)

wasm_str: $(wasm_str_binout)
ifeq ($(WASM),1)
wasm_str_test: wasm_str
	ls -lh $(bin_path)*
else
wasm_str_test: wasm_str
	$(wasm_str_binout) $(webassembly_root)_wasm_.h
endif

$(wasm_str_binout): $(webassembly_root)str/s.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_str_flags)
