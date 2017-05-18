
lang: enum
lang_test: enum_test


enum_binout := $(bin_path)enum$(bin_ext)
enum_cppout := $(tmp_path)enum$(cpp_ext)

enum: $(enum_binout)
enum_test: enum
	$(enum_binout)

$(enum_binout): $(enum_cppout)
	$(CC) $(CFLAGS) $^ $(bin_out)$@

$(enum_cppout): $(src_path)enum/e.c
	$(CPP) $(CPPFLAGS) $^ $(cpp_out)$@
