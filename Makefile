# Top level makefile, the real shit is at src/Makefile

export PREFIX?=$(PWD)
export INSTALL_BIN=$(PREFIX)/bin
export CFLAGS=-Wall -g
OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
	DEBUG := lldb
else
	DEBUG := gdb
endif
export DEBUG

.PHONY: install run debug

default: all

.DEFAULT:
	cd src/hi && $(MAKE)
	cd src/bits && $(MAKE)

install: all
	test -d $(INSTALL_BIN) || mkdir -p $(INSTALL_BIN)
	cd src/hi && $(MAKE) install
	cd src/bits && $(MAKE) install

run: 
	cd src/$(WHAT) && $(MAKE) run

debug:
	cd src/$(WHAT) && $(MAKE) debug

clean:
	cd src/hi && $(MAKE) clean
	cd src/bits && $(MAKE) clean
	rm -f $(INSTALL_BIN)/*
