#!/bin/sh

rm -rf Makefile Makefile.in aclocal.m4 config.cache config.log config.status configure

aclocal \
&& autoconf \
&& automake --add-missing --copy --foreign

