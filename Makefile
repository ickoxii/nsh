#!/usr/bin/make -f

VERSION = 0.1

# Search for .c files in src/ and .h files in include/
# (small hammer)
vpath %.c src
vpath %.h include

# Compilation options
CFLAGS = -Wall -Werror -Wextra -Wpedantic
INCLUDES = -I include
CC = clang
PROGRAM = nsh

# COMPILE.c = $(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(TARGET_ARCH) -c

SOURCES = main.c nsh.c
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)
OUTPUT_OPTION = -o $@

.PHONY: build
build: $(DEPS) $(PROGRAM) cleanup ## Default target

$(PROGRAM): $(OBJECTS) ## Linking rule

%.o: %.c ## Generic compilation rule
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.d: %.c ## Generic dependency rule
	$(CC) -M $(INCLUDES) $< > $@

.PHONY: cleanup
cleanup: ## Clean objects after generating executable
	rm -f $(OBJECTS)
	
.PHONY: clean
clean: ## Clean object, dependency and binary files
	rm -f $(OBJECTS) $(PROGRAM) $(DEPS)

.PHONY: help
help: ## Help function
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
