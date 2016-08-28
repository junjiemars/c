
default: build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile

install: 
	$(MAKE) -f objs/Makefile install

