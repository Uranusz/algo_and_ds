#
# common definitions for all make files to build C/C++ program...
#
BINDIR := bin

SOURCES = $(strip $(wildcard *.c *.cc *.cxx *.cpp))
HEADERS = $(strip $(wildcard *.h *.hh *.hxx *.hpp))
OBJNAMES = $(strip $(patsubst %,%.o, $(basename $(SOURCES))))
LOCALOBJS = $(addprefix $(OBJDIR)/, $(OBJNAMES))

$(BINDIR):
	@mkdir $(BINDIR)

PLATFORM = $(shell $(ROOT)/systype.sh)

%: %.c | $(BINDIR)
	$(LINK.c) $< $(STDLIBS) -o $@ 
	@mv $@ $(BINDIR)/
	@if [ $(PLATFORM) = "macos" ]; \
		then \
		mv $@.dSYM $(BINDIR)/; \
	 fi\
	
%: %.cc | $(BINDIR)
	$(LINK.c) $< $(STDLIBS) -o $@ 
	@mv $@ $(BINDIR)/
	@if [ $(PLATFORM) = "macos" ]; \
		then \
		mv $@.dSYM $(BINDIR)/; \
	 fi\

%: %.cpp | $(BINDIR)
	$(LINK.c) $< $(STDLIBS) -o $@ 
	@mv $@ $(BINDIR)/
	@if [ $(PLATFORM) = "macos" ]; \
		then \
		mv $@.dSYM $(BINDIR)/; \
	 fi\

%: %.cxx | $(BINDIR)
	$(LINK.c) $< $(STDLIBS) -o $@ 
	@mv $@ $(BINDIR)/
	@if [ $(PLATFORM) = "macos" ]; \
		then \
		mv $@.dSYM $(BINDIR)/; \
	 fi\

show:
	@echo "\n---------- Happy coding! ----------"
	@echo "  Sub Directories:"
	@echo "    $(DIRS)"
	@echo "  Source Files:"
	@echo "    $(SOURCES)"
	@echo "  Headers:"
	@echo "    $(HEADERS)"
	@echo "  Objects:"
	@echo "    $(LOCALOBJS)"
	@echo "\n"

clean:
	@echo "remove ./bin..."
	@rm -rf $(BINDIR)

.PHONY: show clean
