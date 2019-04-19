# ./configure --has-env

env: var
env_test: var_test

env_prefix := env
INC += -I$(env_root)

# var
var_binout := $(bin_path)$(env_prefix)_var$(bin_ext)

$(var_binout): $(env_root)var/var.c
	$(CC) $(CFLAGS) $(INC) $< $(bin_out)$@ 

var: $(var_binout)
var_test: var
	$(var_binout) --COUNT=2 --TEXT=Bonjour
	COUNT=2 $(var_binout)
	COUNT=3 TEXT="Bonjor" $(var_binout)
	COUNT=2 $(var_binout) --TEXT=Bonjour


# end of file
