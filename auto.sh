#!/bin/bash

MAKE=${MAKE:=make}

for d in $(find src -maxdepth 1 -mindepth 1 -type d); do
    echo $d
    test -f "$d/Makefile" && ${MAKE} --makefile=Makefile --directory=${d} $@
done
