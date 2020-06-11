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
             wasm_export
webassembly_test: wasm_basic_test								\
                  wasm_export_test


INC += -I$(webassembly_root)
wasm_prefix := wasm
wasm_flags :=
ifeq ($(WASM),1)
	wasm_flags := -s WASM=1
	CFLAGS += -DWASM=1
	bin_ext := .html
endif


# basic
wasm_basic_flags := $(CFLAGS) $(wasm_flags)
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
	$(CC) $(wasm_basic_flags) $(INC) $^ $(bin_out)$@

# export fn
wasm_export_flags := $(CFLAGS) $(wasm_flags) \
                     -s NO_EXIT_RUNTIME=1 \
                     -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
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
	$(CC) $(wasm_export_flags) $(INC) $^ $(bin_out)$@
