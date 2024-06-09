#!/usr/bin/make -f

# >>>> VARS >>>>
srcdir = ./src
includedir = ./include
builddir = ./build
bindir = ./bin
doxydir = ./docs/html ./docs/latex

MAIN = main.c
CFILES = nsh.c
EXE = a.out

CDEBUG = -g

TMAIN = test.c
TEXE = test.out

CFLAGS=-Iinclude -Wall -Wextra -Werror -Wpedantic
# <<<< VARS <<<<

# >>>> PHONIES >>>>
.PHONY: all
all: build run

.PHONY: debug
debug: src/main.c src/nsh.c include/nsh.h
	clang -DDEBUG -o $(bindir)/$(EXE) $(CFLAGS) src/main.c src/nsh.c

.PHONY: build
build: src/main.c src/nsh.c include/nsh.h
	clang -o $(bindir)/$(EXE) $(CFLAGS) $(srcdir)/$(MAIN) $(srcdir)/$(CFILES)

.PHONY: run
run:
	$(bindir)/$(EXE)

.PHONY: verify
verify: src/main.c src/nsh.c include/nsh.h
	clangd --check=src/main.c --check=src/nsh.c --check=include/nsh.h

.PHONY: build-test
build-test: src/test.c src/nsh.c include/nsh.h
	clang $(CFLAGS) $(srcdir)/$(TMAIN) $(srcdir)/$(CFILES) -o $(bindir)/$(TEXE)

.PHONY: run-test
run-test:
	$(bindir)/$(TEXE)

.PHONY: clean
clean:
	rm -f $(bindir)/*
	rm -rf $(doxydir)
	find $(builddir)/ -type f ! -name compile_commands.json -exec rm {} +
# <<<< PHONIES <<<<

# >>>> RULES >>>>

# <<<< RULES <<<<
