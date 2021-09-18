# normal:
# ./configure --has-webassembly --with-std=no
#
#
# emsdk: (optional)
# <emsdk_root>/upstream/emscripten/emconfigure ./configure --has-webassembly --with-std=no
# [WASM=1] <emsdk_root>/upstream/emscripten/emmake make -k -C$(CURDIR) clean test
# source <emsdk_root>/emsdk_env.sh
#
# include:
# <script async type="text/javascript" src="wasm_basic.js"></script>
# in html file
#


emsdk_git_src := 'https://github.com/emscripten-core/emsdk.git'
emsdk_home := $(webassembly_root)/emsdk_home


webassembly: wasm_basic                         \
             wasm_bidir                         \
             wasm_export                        \
             wasm_file                          \
             wasm_str                           \
             wasm_type

webassembly_test: wasm_basic_test               \
                  wasm_bidir_test               \
                  wasm_export_test              \
                  wasm_file_test                \
                  wasm_str_test                 \
                  wasm_type_test


INC += -I$(webassembly_root)

wasm_prefix := wasm
wasm_flags :=


ifeq ($(WASM),1)
  wasm_flags := -s WASM=1
  CFLAGS += -DWASM=1
  bin_ext := .html

  wasm_basic_flags := $(wasm_flags)
  wasm_bidir_flags := $(wasm_flags)                           \
                      -s SAFE_HEAP=1                          \
                      -s "EXPORTED_RUNTIME_METHODS=['ccall']"
  wasm_export_flags := $(wasm_flags)                          \
                     -fsanitize=undefined                     \
                     -s NO_EXIT_RUNTIME=1                     \
                     -s "EXPORTED_RUNTIME_METHODS=['ccall']"  \
                     -s SAFE_HEAP=1
  wasm_file_flags := $(wasm_flags)                                \
                     -s NO_EXIT_RUNTIME=1                         \
                     --preload-file $(webassembly_root)/file/@f.c
  wasm_str_flags := $(wasm_flags)                                   \
                    -s NO_EXIT_RUNTIME=1                            \
                    -s SAFE_HEAP=1                                  \
                    -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
  wasm_type_flags := $(wasm_flags)                          \
                     -s NO_EXIT_RUNTIME=1                   \
                    -s SAFE_HEAP=1                          \
                    -s ASSERTIONS=1                         \
                    -s "EXPORTED_RUNTIME_METHODS=['ccall']"
endif


emsdk_cc := $(emsdk_home)/upstream/emscripten/emcc

$(emsdk_home):
	git clone --depth=1 --branch=main $(emsdk_git_src) $@
emsdk_activate: $(emsdk_home)
	$(emsdk_home)/emsdk install latest
	$(emsdk_home)/emsdk activate latest



# basic
wasm_basic_binout := $(bin_path)/$(wasm_prefix)_basic$(bin_ext)

wasm_basic: emsdk_activate $(wasm_basic_binout)
ifeq ($(WASM),1)
wasm_basic_test: wasm_basic
	ls -lh $(bin_path)/*
else
wasm_basic_test: wasm_basic
	$(wasm_basic_binout)
endif

$(wasm_basic_binout): $(webassembly_root)/basic/b.c
	$(emsdk_cc) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_basic_flags)

# bidir: ./configure --with-std=no
wasm_bidir_binout := $(bin_path)/$(wasm_prefix)_bidir$(bin_ext)

wasm_bidir: $(wasm_bidir_binout)
ifeq ($(WASM),1)
wasm_bidir_test: wasm_bidir
	ls -lh $(bin_path)/*
else
wasm_bidir_test: wasm_bidir
	$(wasm_bidir_binout)
endif

$(wasm_bidir_binout): $(webassembly_root)/bidir/bd.c
	$(emsdk_cc) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_bidir_flags)


# export fn
wasm_export_binout := $(bin_path)/$(wasm_prefix)_export$(bin_ext)

wasm_export: $(wasm_export_binout)
ifeq ($(WASM),1)
wasm_export_test: wasm_export
	ls -lh $(bin_path)/*
else
wasm_export_test: wasm_export
	$(wasm_export_binout)
endif

$(wasm_export_binout): $(webassembly_root)/export/x.c
	$(emsdk_cc) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_export_flags)

# file
wasm_file_binout := $(bin_path)/$(wasm_prefix)_file$(bin_ext)

wasm_file: $(wasm_file_binout)
ifeq ($(WASM),1)
wasm_file_test: wasm_file
	ls -lh $(bin_path)/*
else
wasm_file_test: wasm_file
	$(wasm_file_binout) $(webassembly_root)/_wasm_.h
endif

$(wasm_file_binout): $(webassembly_root)/file/f.c
	$(emsdk_cc) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_file_flags)


# str
wasm_str_binout := $(bin_path)/$(wasm_prefix)_str$(bin_ext)

wasm_str: $(wasm_str_binout)
ifeq ($(WASM),1)
wasm_str_test: wasm_str
	ls -lh $(bin_path)/*
else
wasm_str_test: wasm_str
	$(wasm_str_binout) $(webassembly_root)/_wasm_.h
endif

$(wasm_str_binout): $(webassembly_root)/str/s.c
	$(emsdk_cc) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_str_flags)

# type
wasm_type_binout := $(bin_path)/$(wasm_prefix)_type$(bin_ext)

wasm_type: $(wasm_type_binout)
ifeq ($(WASM),1)
wasm_type_test: wasm_type
	ls -lh $(bin_path)/*
else
wasm_type_test: wasm_type
	$(wasm_type_binout) $(webassembly_root)/_wasm_.h
endif

$(wasm_type_binout): $(webassembly_root)/type/t.c
	$(emsdk_cc) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(wasm_type_flags)


.PHONY: emsdk_activate


# eof
