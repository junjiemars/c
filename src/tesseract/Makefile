# ./configure --has-io

tesseract: tesseract_basic
tesseract_test: tesseract_basic_test

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
