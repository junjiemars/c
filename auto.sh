#!/bin/bash

MAKE=${MAKE:=make}

for d in $(find src -type d -depth 1); do
    echo $d
    test -f "$d/makefile" && ${MAKE} --makefile=Makefile --directory=${d} $@
done
