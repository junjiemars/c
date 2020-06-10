# normal:
# ./configure --has-webassembly 
# emsdk:
# <emsdk_root>/upstream/emscripten/emconfigure ./configure --has-webassembly
# [WASM=1] <emsdk_root>/upstream/emscripten/emmake make -k -C$(CURDIR) clean test
#

webassembly: wasm_basic
webassembly_test: wasm_basic_test


INC += -I$(webassembly_root)
wasm_prefix := wasm
wasm_flags :=
ifeq ($(WASM),1)
	wasm_flags := -s WASM=1
	CFLAGS += -DWASM=1
	bin_ext := .html
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
	$(CC) $(CFLAGS) $(wasm_flags) $(INC) $^ $(bin_out)$@

