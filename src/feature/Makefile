# ./configure --has-feature

ifeq ($(CC_NAME),gcc)
  include $(CURDIR)/src/feature/gcc/Makefile
else ifeq ($(CC_NAME),clang)
  include $(CURDIR)/src/feature/clang/Makefile
endif
