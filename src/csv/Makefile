
csv_binout := $(bin_path)csv$(bin_ext)

csv: $(csv_binout)
csv_test: csv
	$(csv_binout) "src/csv/x.csv"

$(csv_binout): $(src_path)p.c
	$(CC) $(CFLAGS) $^ $(bin_out)$@
