# Top level makefile, the real shit is at src/Makefile

PREFIX?=$(PWD)
export PREFIX
export INSTALL_BIN=$(PREFIX)/bin

.PHONY: install

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

clean:
	cd src/hi && $(MAKE) clean
	cd src/bits && $(MAKE) clean
	rm -f $(INSTALL_BIN)/*
