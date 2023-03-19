#
# ./configure --has-leet
# make clean test
#


leet: leet_roman_number \
      leet_int_to_words

leet_test: leet_roman_number \
           leet_int_to_words


# env
leet_prefix := leet

INC += $(nm_inc_opt)$(leet_root) $(nm_inc_opt)$(root)/posix

ifeq ($(_MEMORY_),1)
	CFLAGS += $(f_sanitize)
endif


# roman_number
leet_roman_number_b1_binout := \
	$(bin_path)/$(leet_prefix)_roman_number_b1$(bin_ext)
leet_roman_number_r1_binout := \
	$(bin_path)/$(leet_prefix)_roman_number_r1$(bin_ext)

leet_roman_number: $(leet_roman_number_b1_binout) \
                   $(leet_roman_number_r1_binout)
leet_roman_number_test: leet_roman_number_b1_test \
                        leet_roman_number_r1_test

leet_roman_number_b1_test: $(leet_roman_number_b1_binout)
	$< "MCMXCIV"
leet_roman_number_r1_test: $(leet_roman_number_r1_binout)
	$< "MCMXCIV"

$(leet_roman_number_b1_binout): $(leet_root)/roman_number/d.c   \
                                $(leet_root)/roman_number/b1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@

$(leet_roman_number_r1_binout): $(leet_root)/roman_number/d.c   \
                                $(leet_root)/roman_number/r1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@


# int_to_words
leet_int_to_words_b1_binout := \
	$(bin_path)/$(leet_prefix)_int_to_words_b1$(bin_ext)

leet_int_to_words: $(leet_int_to_words_b1_binout)
leet_int_to_words_test: leet_int_to_words_b1_test

leet_int_to_words_b1_test: $(leet_int_to_words_b1_binout)
	$< "123456789"

$(leet_int_to_words_b1_binout): $(leet_root)/int_to_words/d.c   \
                                $(leet_root)/int_to_words/b1.c
	$(CC) $(CFLAGS) $(INC) $^ $(bin_out)$@
