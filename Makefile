MAIN=src/main.c
CFILES=src/nsh.c
EXE=bin/a.out

TMAIN=src/test.c
TEXE=bin/test.out

CFLAGS=-Iinclude -Wall -Wextra -Werror -Wpedantic

debug: src/main.c src/nsh.c include/nsh.h
	clang -DDEBUG -o $(EXE) $(CFLAGS) src/main.c src/nsh.c

build: src/main.c src/nsh.c include/nsh.h
	clang -o $(EXE) $(CFLAGS) $(MAIN) $(CFILES)

run:
	$(EXE)

verify:
	clangd --check=src/main.c --check=src/nsh.c --check=include/nsh.h

build-test: src/test.c src/nsh.c include/nsh.h
	clang $(CFLAGS) $(TMAIN) $(CFILES) -o $(TEXE)

run-test:
	$(TEXE)

.PHONY: build, run, verify, build-test, run-test
