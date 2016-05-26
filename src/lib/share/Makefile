ifeq ($(OS),Darwin)
	CFLAGS += -dynamiclib
else ifeq ($(OS),Linux)
	CFLAGS += -fPIC -shared
endif
export CFLAGS

default: share$(LIB_SUFFIX)

share$(LIB_SUFFIX): share.c
	$(CC) $(CFLAGS) $^ -o share$(LIB_SUFFIX)
	@(cp $@ ../)

install: share.$(LIB_SUFFIX)
	@(cp $^ $(INSTALL_BIN)/)

clean:
	-(test $(LIB_SUFFIX) && rm -r share$(LIB_SUFFIX)*)
