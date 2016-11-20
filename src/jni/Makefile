
square_lib := $(lib_path)libsquare$(mod_ext)


jni: $(square_lib)

jni_jflags += -g
jni_lflags += $(LFLAGS) $(INC)
jni_ldflags += $(LDFLAGS)

java2c_class := $(bin_path)Java2c.class
square_h := $(inc_path)square.h

$(java2c_class): $(src_path)Java2c.java
	$(JC) $(jni_jflags) -d $(bin_path) $^

$(square_h): $(java2c_class)
	$(JH) -o $@ -cp .$(nm_p)$(bin_path) Java2c 

$(square_lib): $(square_h) $(src_path)square.c
	$(CC) $(jni_lflags) $(jni_ldflags) $(src_path)square.c $(bin_out)$@

jni_test: jni
	$(JAVA) -cp .$(nm_p)$(bin_path)$(nm_p)$(lib_path) -Djava.library.path=$(lib_path) Java2c

