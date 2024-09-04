# -*- mode:makefile-gmake -*-
#
# ./configure --has-leptonica --has-tesseract
#

ifeq ($(has_tesseract_required),YES)
tesseract: tesseract_basic                      \
           tesseract_pdf                        \
           tesseract_rust

tesseract_test: tesseract_basic_test            \
                tesseract_pdf_test              \
                tesseract_rust_test
else
tesseract:
tesseract_test: tesseract
	@echo "#skip ... no all tesseract requirements found"
endif



# env
tesseract_prefix := tesseract

tesseract_out := $(CURDIR)/$(out)/var/tesseract
tesseract_git_src := 'https://github.com/tesseract-ocr/tesseract.git'
tesseract_git_data := 'https://github.com/tesseract-ocr/tessdata.git'
tesseract_eng_traineddata := 'https://raw.githubusercontent.com/tesseract-ocr/tessdata/main/eng.traineddata'
tesseract_home := $(tesseract_root)/tesseract_home
tesseract_inc_dir := $(tesseract_out)/include
tesseract_lib_dir := $(tesseract_out)/lib
tesseract_tessdata_dir := $(tesseract_out)/share/tessdata
tesseract_tessdata := $(tesseract_tessdata_dir)/eng.traineddata

tesseract_build := $(tesseract_out)/include/tesseract/capi.h
 # $(tesseract_lib_dir)/pkgconfig $(tesseract_tessdata)

INC += $(nm_inc_opt)$(root)
INC += $(nm_inc_opt)$(root)/posix
INC += $(nm_inc_opt)$(leptonica_root)
INC += $(nm_inc_opt)$(tesseract_root)
INC += $(nm_inc_opt)$(tesseract_inc_dir)
tesseract_libs += $(nm_libdir_opt)$(tesseract_lib_dir) $(nm_lib_opt)tesseract
tesseract_libs += $(nm_libdir_opt)$(leptonica_lib_dir) $(nm_lib_opt)leptonica
tesseract_lib_path = $(tesseract_lib_dir)$(nm_path_sep)$(leptonica_lib_dir)

# cc options
tesseract_cc_opt :=
tesseract_ld_opt :=
tesseract_debug_opt :=
tesseract_cc_opt += $(nm_release_opt)
tesseract_cc_opt += $(nm_optimize_opt)
tesseract_cc_opt += $(nm_symbol_opt)

# build tesseract
PKG_CONFIG_PATH := $(tesseract_lib_dir)/pkgconfig
tesseract_example_png := $(tesseract_example_png)

has_tesseract: $(tesseract_build) \
               $(tesseract_tessdata)

$(tesseract_build): $(leptonica_build) \
                    $(tesseract_home)
	cd $(tesseract_home) \
    && ./autogen.sh \
    && CFLAGS="$(tesseract_cc_opt)" \
       PKG_CONFIG_PATH="$(leptonica_lib_dir)/pkgconfig" \
       ./configure --prefix=$(tesseract_out) \
    && make -C . -j4 install


$(tesseract_home):
	git clone --depth=1 --branch=main $(tesseract_git_src) $@

$(tesseract_tessdata):
	curl $(tesseract_eng_traineddata) -o $@



# basic
tesseract_basic_binout := $(bin_path)/$(tesseract_prefix)_basic$(bin_ext)

tesseract_basic: has_tesseract \
                 $(tesseract_basic_binout)
tesseract_basic_test: tesseract_basic
	LD_LIBRARY_PATH=$(tesseract_lib_path) \
		$(tesseract_basic_binout) $(tesseract_example_png)

$(tesseract_basic_binout): $(tesseract_root)/basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(tesseract_libs)



# pdf
tesseract_pdf_binout := $(bin_path)/$(tesseract_prefix)_pdf$(bin_ext)

tesseract_pdf: has_tesseract \
               $(tesseract_pdf_binout)
tesseract_pdf_test: tesseract_pdf
	LD_LIBRARY_PATH=$(tesseract_lib_path) \
		$(tesseract_pdf_binout) $(tesseract_example_png) \
			$(CURDIR)/$(tmp_path)$(tesseract_prefix)_out 5000

$(tesseract_pdf_binout): $(tesseract_root)/pdf/pdf.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(tesseract_libs)



# rust
tesseract_rust_cargo := $(tesseract_root)/rust/Cargo.toml
tesseract_rust_name := $(tesseract_prefix)_rust$(bin_ext)
tesseract_rust_binout := $(bin_path)/$(tesseract_rust_name)
tesseract_cargo_target_dir := $(CURDIR)/$(tmp_path)
tesseract_cargo_out_dir := "$(tesseract_cargo_target_dir)/debug"
# https://github.com/thomasgruebl/rusty-tesseract

ifeq ($(has_tesseract_rust_required),YES)
tesseract_rust: $(tesseract_rust_binout)
tesseract_rust_test: tesseract_rust
	$(tesseract_rust_binout)
else
tesseract_rust:
tesseract_rust_test: tesseract_rust
	@echo "#skip ... no all rust requirements found"
endif

$(tesseract_rust_cargo):
	$(CARGO) new --bin --vcs=none \
		--name $(tesseract_prefix)_rust $(tesseract_root)/rust
	$(CARGO) add --manifest-path=$@ rusty-tesseract


$(tesseract_rust_binout): $(tesseract_rust_cargo)
	$(CARGO) build \
    --manifest-path $< \
    --target-dir $(tesseract_cargo_target_dir) \
  && cp $(tesseract_cargo_out_dir)/$(tesseract_rust_name) $@



# clean
tesseract_clean: clean \
                 clean_tesseract_home


clean_tesseract_home:
	-$(RM) -rf $(tesseract_home)

clean_tesseract_out:
	test ! -f $(CURDIR)/$(tesseract_home)/Makefile \
    || make -C $(CURDIR)/$(tesseract_home) clean
	test ! -d $(tesseract_out) || rm -r $(tesseract_out)

clean_tesseract_bin:
	test ! -f $(tesseract_basic_binout) \
    || rm $(tesseract_basic_binout)


.PHONY: tesseract_clean                         \
        clean_tesseract_out                     \
        clean_tesseract_bin                     \
        tesseract tesseract_test

# eof
