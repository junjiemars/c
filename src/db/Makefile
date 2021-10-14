# ./configure --has-db


db: db_mysql

db_test: db_mysql_test

# env
db_prefix := db

INC += -I$(root) -I$(db_root)


# db_mysql
db_mysql_basic_binout := $(bin_path)/$(db_prefix)_mysql_basic$(bin_ext)

ifeq (yes, $(has_mysqlclient))
db_mysql: $(db_mysql_basic_binout)
else
db_mysql:
	@echo "#skip db_mysql_test ..."
endif
db_mysql_test: db_mysql

$(db_mysql_basic_binout): $(db_root)/mysql/b.c
	$(CC) $(CFLAGS) $(INC) $(db_mysql_cflags) $^ $(bin_out)$@ $(db_mysql_ldlibs)


.PHONY: db_mysql db_mysql_test

# eof
