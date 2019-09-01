CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -O2 -fPIC
LD := gcc
LDFLAGS :=

.PHONY: all types clean

all: libsimplelist.so types

types: types.vim

types.vim: *.h
	ctags -o- --kinds-c++=tcA *.cpp *.c *.h |\
		awk '{print "syntax keyword Type " $$1}' > $@

libsimplelist.so: simplelist.o Makefile
	$(LD) $(LDFLAGS) -shared $< -o $@
simplelist.o: simplelist.c simplelist.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) *.o *.so types.vim
