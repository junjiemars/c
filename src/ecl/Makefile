

ecl: embed
ecl_test: embed_test

INC += -Isrc/ecl/


embed_binout := $(bin_path)hello$(bin_ext)
embed_objout := $(tmp_path)hello.a

embed: $(embed_binout)
embed_test: embed
	$(embed_binout)

$(embed_binout): $(src_path)embed/hello.c $(embed_objout)
	$(CC) $(INC) $(shell ecl-config --cflags) $(bin_out)$@ $^ $(shell ecl-config --ldflags) -lecl

$(embed_objout): $(src_path)embed/hello-lisp.lisp
	ecl -norc \
	    -eval '(require :asdf)' \
	    -eval '(push "src/ecl/embed/" asdf:*central-registry*)' \
	    -eval '(asdf:make-build :hello-lisp :type :static-library :move-here "src/ecl/embed/" :init-name "init_lib_HELLO_LISP")' \
	    -eval '(quit)'
	cp $(src_path)embed/hello-lisp.a $(embed_objout)



#hello.exe: hello.c hello-lisp.a
#	$(CC) `ecl-config --cflags` -o $@ hello.c hello-lisp.a \
#	      `ecl-config --ldflags` -lecl
#
#hello-lisp.a: hello-lisp.lisp
#	ecl -norc \
#	    -eval '(require :asdf)' \
#	    -eval '(push "./" asdf:*central-registry*)' \
#	    -eval '(asdf:make-build :hello-lisp :type :static-library :move-here "./" :init-name "init_lib_HELLO_LISP")' \
#	    -eval '(quit)'
#
#clean:
#	-rm -f hello-lisp.a hello.exe
