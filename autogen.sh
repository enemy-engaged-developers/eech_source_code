#!/bin/sh

rm -rf Makefile Makefile.in aclocal.m4 config.cache config.log config.status configure

aclocal \
&& autoconf \
&& automake --add-missing --copy --foreign

# Hack to ensure "-I." doesn't appear in the CFLAGS in these two directories.
# Otherwise the time.h present there conflicts with the system <time.h>.
for i in modules/system/Makefile.in modules/system/external/Makefile.in; do
    if [ -f "$i" ]; then
        perl -p -i -e 's/^(DEFS =.* )-I\. -I\$\(srcdir\)/$1/' "$i"
    fi
done
