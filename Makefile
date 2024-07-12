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
DOXY_DIR = docs/html docs/latex

.PHONY: help
help: ## Help function
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: build
build: $(DEPS) $(PROGRAM) clean-obj ## Default target
	@echo "=========="
	@echo "Project built"
	@echo "Run ./$(PROGRAM) to run the shell"

$(PROGRAM): $(OBJECTS) ## Linking rule

%.o: %.c ## Generic compilation rule
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.d: %.c ## Generic dependency rule
	$(CC) -M $(INCLUDES) $< > $@

.PHONY: clean-obj
clean-obj: ## Clean objects after generating executable
	rm -f $(OBJECTS)

.PHONY: clean-dep
clean-dep: ## Clean dependency files
	rm -f $(DEPS)

.PHONY: clean-doxy
clean-doxy: ## Clean doxygen documentation files
	rm -rf $(DOXY_DIR)
	
.PHONY: clean
clean: clean-obj clean-dep clean-doxy ## Clean all generated files
	rm -f $(PROGRAM)

