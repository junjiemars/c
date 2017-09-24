#!/bin/bash

[ -f "Makefile" ] && make clean

case "$TRAVIS_OS_NAME" in
  osx)
    ./configure \
			--with-std=c11 \
			--has-library \
			--has-memory \
			--has-x86 \
			--has-ds \
			--has-lang
    make -j4
  ;;

  linux|*)
    ./configure \
			--with-std=c11 \
			--has-library \
			--has-memory \
			--has-x86 \
			--has-ds \
			--has-lang
    make -j4
  ;;
esac

