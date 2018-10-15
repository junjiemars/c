#!/bin/bash

CC=
case "$TRAVIS_OS_NAME" in
  osx) CC=clang ;;
  linux) CC=gcc ;;
	*)
		# just for testing on Windows and it's not part of Travis.
		case "`uname -s`" in
			MSYS_NT-*|MINGW??_NT-*) CC=cl ;;
			*) CC=gcc ;;
		esac
		;;
esac

CC=$CC ./configure \
	--has-ds \
	--has-hi \
	--has-lang \
	--has-memory \
	--has-x86
make clean test

