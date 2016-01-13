ROOT = ..
PLATFORM = $(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)
include $(ROOT)/Make.include.cxx

#
# all targets to build...
# we can build them one by one like:
#     make array_to_BST
# or just
#     make all
# to build all targets.
#

#
# all targets...
# each of the source files has an entry point 'main()', so we can generate
# the target names by this way...
#
TARGETS = $(basename $(SOURCES))

all: $(TARGETS)

help:
	@echo "Targets to build:"
	@echo "  $(TARGETS)\n"
	@echo "  'make <target>' to build single target;"
	@echo "  'make all' to build whole targets.\n"

.PHONY: all help 
