#!/bin/bash

if [ -z "$TRAVIS_OS_NAME" ]; then
	TRAVIS_OS_NAME="`uname -s`"
fi

case "$TRAVIS_OS_NAME" in
  osx|Darwin) CC=clang ;;
  linux|Linux) CC=gcc ;;
	MSYS_NT-*|MINGW??_NT-*) CC=cl ;;
	*) CC=gcc ;;
esac

CC=$CC ./configure \
	--has-ds \
	--has-hi \
	--has-lang \
	--has-memory \
	--has-x86
make clean test

