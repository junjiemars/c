# -*- mode:makefile-gmake -*-
#
# ./configure --has-leptonica --has-tesseract
#


tesseract: tesseract_basic                      \
           tesseract_pdf

tesseract_test: tesseract_basic_test            \
                tesseract_pdf_test



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

tesseract_build := $(tesseract_out)/include/tesseract/capi.h
tesseract_tessdata := $(tesseract_tessdata_dir)/eng.traineddata

INC += $(nm_inc_opt)$(root)
INC += $(nm_inc_opt)$(root)/posix
INC += $(nm_inc_opt)$(leptonica_root)
INC += $(nm_inc_opt)$(tesseract_root)
INC += $(nm_inc_opt)$(tesseract_inc_dir)
tesseract_libs += $(nm_libdir_opt)$(tesseract_lib_dir) $(nm_lib_opt)tesseract
tesseract_libs += $(nm_libdir_opt)$(leptonica_lib_dir) $(nm_lib_opt)leptonica
tesseract_lib_path = $(tesseract_lib_dir)$(nm_path_sep)$(leptonica_lib_dir)

$(tesseract_tessdata): $(tesseract_build)
	curl $(tesseract_eng_traineddata) -o $@

$(tesseract_build): $(leptonica_build) \
                    $(tesseract_home)
	cd $(tesseract_home) \
    && ./autogen.sh \
    && ./configure --prefix=$(tesseract_out) \
    && make -C . -j4 install

$(tesseract_home):
	git clone --depth=1 --branch=main $(tesseract_git_src) $@

export PKG_CONFIG_PATH = $(tesseract_lib_dir)/pkgconfig



# basic
tesseract_basic_binout := $(bin_path)/$(tesseract_prefix)_basic$(bin_ext)

tesseract_basic: $(tesseract_tessdata) \
                 $(tesseract_basic_binout)
tesseract_basic_test: tesseract_basic
	LD_LIBRARY_PATH=$(tesseract_lib_path) \
		$(tesseract_basic_binout) $(CURDIR)/src/tesseract/example.png

$(tesseract_basic_binout): $(tesseract_root)/basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(tesseract_libs)



# pdf
tesseract_pdf_binout := $(bin_path)/$(tesseract_prefix)_pdf$(bin_ext)

tesseract_pdf: $(tesseract_tessdata) \
               $(tesseract_pdf_binout)
tesseract_pdf_test: tesseract_pdf
	LD_LIBRARY_PATH=$(tesseract_lib_path) \
		$(tesseract_pdf_binout) $(CURDIR)/src/tesseract/example.png \
			$(CURDIR)/$(tmp_path)$(tesseract_prefix)_out 5000

$(tesseract_pdf_binout): $(tesseract_root)/pdf/pdf.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(tesseract_libs)



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
        clean_leptoonica_home                   \
        clean_tesseract_out                     \
        clean_tesseract_bin                     \
        tesseract_basic tesseract_basic_test

# eof
