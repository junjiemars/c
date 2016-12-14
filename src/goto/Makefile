
goto_binout := $(bin_path)goto$(bin_ext)

goto: $(goto_binout)

$(goto_binout): $(src_path)goto.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@

goto_test: goto
	$(goto_binout)

