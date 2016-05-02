# Top level makefile, the real shit is at src/Makefile

export PREFIX?=$(PWD)
export INSTALL_BIN=$(PREFIX)/bin
export CFLAGS=-Wall -g -std=c99 
OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
	DEBUG := lldb
else
	DEBUG := gdb --args 
endif
export DEBUG

default: all

.DEFAULT:
	@(MAKE=${MAKE} ./auto.sh)

run:
	@(cd src/$(what) && $(MAKE) run)

debug:
	@(cd src/$(what) && $(MAKE) debug)

clean:
	@(cd src/$(what) && $(MAKE) clean)

purge:
	@(MAKE=${MAKE} ./auto.sh clean)

install: all
	@(test -d $(INSTALL_BIN) || mkdir -p $(INSTALL_BIN))
	@(MAKE=${MAKE} ./auto.sh install)

uninstall:
	-(rm -f $(INSTALL_BIN)/*)


.PHONY: install run debug uninstall
