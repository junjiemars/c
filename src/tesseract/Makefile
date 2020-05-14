# ./configure --has-io

tesseract: tesseract_basic											\
           tesseract_pdf
tesseract_test: tesseract_basic_test						\
                tesseract_pdf_test

tesseract_prefix := tesseract

INC += -I$(tesseract_root)
INC += $(shell pkg-config --cflags-only-I lept)
INC += $(shell pkg-config --cflags-only-I tesseract|sed 's/leptonica/tesseract/g')
LDFLAGS += $(shell pkg-config --libs lept tesseract)


# basic
tesseract_basic_binout := $(bin_path)$(tesseract_prefix)_basic$(bin_ext)

tesseract_basic: $(tesseract_basic_binout)
tesseract_basic_test: tesseract_basic
	$(tesseract_basic_binout) $(CURDIR)/src/tesseract/example.png

$(tesseract_basic_binout): $(tesseract_root)basic/b.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDFLAGS)

# pdf
tesseract_pdf_binout := $(bin_path)$(tesseract_prefix)_pdf$(bin_ext)

tesseract_pdf: $(tesseract_pdf_binout)
tesseract_pdf_test: tesseract_pdf
	$(tesseract_pdf_binout) $(CURDIR)/src/tesseract/example.png \
		$(CURDIR)/$(tmp_path)$(tesseract_prefix)_out

$(tesseract_pdf_binout): $(tesseract_root)pdf/pdf.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@ $(LDFLAGS)
