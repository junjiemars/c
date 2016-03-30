# Top level makefile, the real shit is at src/Makefile

export PREFIX?=$(PWD)
export INSTALL_BIN=$(PREFIX)/bin
export CFLAGS=-Wall -g
OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
	DEBUG := lldb
else
	DEBUG := gdb --args 
endif
export DEBUG

default: all

.DEFAULT:
	@(cd src/hi && $(MAKE))
	@(cd src/bits && $(MAKE))
	@(cd src/utf8 && $(MAKE))
	@(cd src/str && $(MAKE))
	@(cd src/mem && $(MAKE))
	@(cd src/math && $(MAKE))
	

run:
	@(cd src/$(what) && $(MAKE) run)

debug:
	@(cd src/$(what) && $(MAKE) debug)

clean:
	@(cd src/$(what) && $(MAKE) clean)

install: all
	@(test -d $(INSTALL_BIN) || mkdir -p $(INSTALL_BIN))
	@(cd src/hi && $(MAKE) install)
	@(cd src/bits && $(MAKE) install)
	@(cd src/utf8 && $(MAKE) install)
	@(cd src/str && $(MAKE) install)
	@(cd src/mem && $(MAKE) install)
	@(cd src/math && $(MAKE) install)

uninstall:
	-(rm -f $(INSTALL_BIN)/*)


.PHONY: install run debug uninstall
