CFILES=src/main.c src/nsh.c
EXE=bin/a.out
CFLAGS=-Iinclude -Wall -Wextra -Werror -pedantic

build:
	clang $(CFLAGS) $(MAIN) -o $(EXE)

run:
	$(EXE)

verify:
	clangd --check=src/main.c --check=src/nsh.c --check=include/nsh.h

.PHONY: build, run, verify
