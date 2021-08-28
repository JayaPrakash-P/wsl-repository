#
# (GNU) Makefile for UN*X-like systems
# This makefile shows how to make a different runner for each test
#

.PHONY: all clean

all: CxxTestRunner test

clean:
	rm -f $(CXXTESTDIR)/*~ $(CXXTESTDIR)/*.cpp $(CXXTESTDIR)/*.o $(CXXTESTDIR)/CxxTestRunner

CXXTESTDIR   = ./CxxTests
CXXTESTGEN   = cxxtestgen
CXXTESTFLAGS = --have-eh --abort-on-fail

TESTS = $(wildcard $(CXXTESTDIR)/*Suite.h)
OBJS  = $(CXXTESTDIR)/CxxTestRunner.o $(TESTS:$(CXXTESTDIR)/%.h=$(CXXTESTDIR)/%.o)

CxxTestRunner: $(CXXTESTDIR)/CxxTestRunner
	$(info $$TESTS is [${TESTS}])
	$(info $$OBJS is [${OBJS}])
	rm -f $(CXXTESTDIR)/*~ $(CXXTESTDIR)/*.cpp $(CXXTESTDIR)/*.o

$(CXXTESTDIR)/CxxTestRunner: $(OBJS)
	g++ -o $@ $^

test: test1 test2 test3 test4
	$(info $@ running with [$^])
	$(info $@ running with [$<])

test%:
	$(info $@ running...)

%.o: %.cpp
	g++ -c -o $@ $^

$(CXXTESTDIR)/%.cpp:$(CXXTESTDIR)/%.h
	$(info $$TESTS is [${TESTS}])
	$(info $$OBJS is [${OBJS}])
	$(CXXTESTGEN) $(CXXTESTFLAGS) --part -o $@ $^

$(CXXTESTDIR)/CxxTestRunner.cpp:
	$(CXXTESTGEN) $(CXXTESTFLAGS) --root --error-printer -o $@

#
# Local Variables:
# compile-command: "make -fMakefile.unix"
# End:
#