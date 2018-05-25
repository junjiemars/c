#!/bin/bash

CC=
case "$TRAVIS_OS_NAME" in
  osx) CC=clang ;;
  linux) CC=gcc ;;
	*) : ;;
esac

CC=$CC ./configure \
	--has-ds \
	--has-hi \
	--has-memory \
	--has-x86
make -j4 RISKY=1 clean test

