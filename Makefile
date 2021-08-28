.PHONY: all clean

all: CxxTests

clean:
	rm -f $(CXXTESTDIR)/*~ $(CXXTESTDIR)/*.cpp $(CXXTESTDIR)/*.o $(CXXTESTDIR)/CxxTestRunner

CXXTESTDIR   = ./CxxTests
CXXTESTGEN   = cxxtestgen
CXXTESTFLAGS = --have-eh --abort-on-fail

TESTS = $(wildcard $(CXXTESTDIR)/*Suite.h)
OBJS  = $(CXXTESTDIR)/CxxTestRunner.o $(TESTS:$(CXXTESTDIR)/%.h=$(CXXTESTDIR)/%.o)

CxxTests: $(CXXTESTDIR)/CxxTestRunner
	$(info $$OBJS is [${OBJS}])
	rm -f $(CXXTESTDIR)/*~ $(CXXTESTDIR)/*.cpp $(CXXTESTDIR)/*.o

$(CXXTESTDIR)/CxxTestRunner: $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $^

$(CXXTESTDIR)/%.cpp:$(CXXTESTDIR)/%.h
	$(CXXTESTGEN) $(CXXTESTFLAGS) --part -o $@ $^

$(CXXTESTDIR)/CxxTestRunner.cpp:
	$(CXXTESTGEN) $(CXXTESTFLAGS) --root --error-printer -o $@
