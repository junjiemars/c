#
# ./configure --has-leptonica
#
# install dependencies on ubuntu
# git clone --depth=1 --branch=1 https://github.com/DanBloomberg/leptonica.git
# ./autogen.sh
# ./configure 
# make -j4 install
# sudo ldconfig
#
# git clone --depth=1 --branch=1 https://github.com/tesseract-ocr/tesseract.git
# ./autogen.sh
# ./configure
# sudo make -j4 install
# sudo ldconfig
#
# git clone --depth=1 --branch=1 https://github.com/tesseract-ocr/tessdata.git
#

tesseract: tesseract_basic                      \
           tesseract_pdf

tesseract_test: tesseract_basic_test            \
                tesseract_pdf_test


# env
tesseract_prefix := tesseract

tesseract_out := $(CURDIR)/$(out)/var/tesseract
tesseract_git_src := 'https://github.com/tesseract-ocr/tesseract.git'
tesseract_home := $(tesseract_root)/tesseract_home

tesseract_build := $(tesseract_out)/include/tesseract/capi.h

INC += $(nm_inc_opt)$(tesseract_root)
INC += $(shell pkg-config --cflags-only-I tesseract lept)
LDFLAGS += $(shell pkg-config --libs lept tesseract)

export PKG_CONFIG_PATH = $(leptonica_lib_dir)/pkgconfig

$(tesseract_build):  $(leptonica_build)         \
                     $(tesseract_home)
	cd $(tesseract_home)                          \
    && ./autogen.sh                             \
    && ./configure --prefix=$(tesseract_out)    \
    && make -C . -j4 install


$(tesseract_home):
	git clone --depth=1 --branch=main $(tesseract_git_src) $@


# basic
tesseract_basic_binout := $(bin_path)/$(tesseract_prefix)_basic$(bin_ext)

tesseract_basic: $(tesseract_build) \
                 $(tesseract_basic_binout)
tesseract_basic_test: tesseract_basic
	$(tesseract_basic_binout) $(CURDIR)/src/tesseract/example.png

$(tesseract_basic_binout): $(tesseract_root)/basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDFLAGS)

# pdf
tesseract_pdf_binout := $(bin_path)/$(tesseract_prefix)_pdf$(bin_ext)

tesseract_pdf: $(tesseract_pdf_binout)
tesseract_pdf_test: tesseract_pdf
	$(tesseract_pdf_binout) $(CURDIR)/src/tesseract/example.png \
		$(CURDIR)/$(tmp_path)$(tesseract_prefix)_out              \
    5000

$(tesseract_pdf_binout): $(tesseract_root)/pdf/pdf.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDFLAGS)



# clean
tesseract_clean: clean                          \
                 clean_tesseract_home


clean_tesseract_home:
	-$(RM) -rf $(tesseract_home)

clean_tesseract_out:
	test ! -f $(CURDIR)/$(tesseract_home)/Makefile  \
    || make -C $(CURDIR)/$(tesseract_home) clean
	test ! -d $(tesseract_out) || rm -r $(tesseract_out)

clean_tesseract_bin:
	test ! -f $(tesseract_basic_binout)    \
    || rm $(tesseract_basic_binout)


.PHONY: tesseract_clean                         \
        clean_leptoonica_home                   \
        clean_tesseract_out                     \
        clean_tesseract_bin                     \
        tesseract_basic tesseract_basic_test

# eof
