#
# rules to make java programs
#
BINDIR := bin

SOURCES = $(strip $(wildcard *.java))

$(BINDIR):
	@mkdir $(BINDIR)

%.class: %.java | $(BINDIR)
	$(JC) -d $(BINDIR) $(JFLAGS) $<

clean:
	@echo "remove ./bin..."
	@rm -rf $(BINDIR)
