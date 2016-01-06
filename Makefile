# Top level makefile, the real shit is at src/Makefile

PREFIX?=$(HOME)/bin
INSTALL_BIN=$(PREFIX)

#default: all


.DEFAULT:
	@echo $(INSTALL_BIN)
	@mkdir -p ../bin
	cd src && $(MAKE) $@

bits:
	cd src/bits && $(MAKE) $@

install:
	cd src && $(MAKE) $@

.PHONY: install
