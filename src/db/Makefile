# ./configure --has-db


db: db_mysql

db_test: db_mysql_test


# env
db_prefix := db

INC += $(nm_inc_opt)$(db_root) $(nm_inc_opt)$(root)/posix 


# db_mysql
db_mysql_basic_binout := $(bin_path)/$(db_prefix)_mysql_basic$(bin_ext)

ifeq ($(has_mysqlclient), yes)
db_mysql: $(db_mysql_basic_binout)
db_mysql_test: db_mysql
	$(db_mysql_basic_binout) -h
	$(db_mysql_basic_binout)
else
db_mysql:
	@echo "#skip db_mysql_test ..."
db_mysql_test: db_mysql
endif



$(db_mysql_basic_binout): $(db_root)/mysql/b.c
	$(CC) $(CFLAGS) $(INC) $(db_mysql_cflags) $^ $(bin_out)$@ $(db_mysql_ldlibs)



.PHONY: db_mysql db_mysql_test



# eof
