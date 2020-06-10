# normal:
# ./configure --has-webassembly 
# emsdk:
# <emsdk_root>/upstream/emscripten/emconfigure ./configure --has-webassembly
# <emsdk_root>/upstream/emscripten/emmake make -k -C$(CURDIR) clean test
#

webassembly: wasm_basic
webassembly_test: wasm_basic_test


INC += -I$(webassembly_root)
wasm_prefix := wasm
wasm_flags :=

# basic
wasm_flags := -s WASM=1
wasm_basic_binout := $(bin_path)$(wasm_prefix)_basic.html

wasm_basic: $(wasm_basic_binout)
wasm_basic_test: wasm_basic
	ls -lh $(bin_path)*

$(wasm_basic_binout): $(webassembly_root)basic/b.c
	$(CC) $(CFLAGS) $(wasm_flags) $(INC) $^ $(bin_out)$@

