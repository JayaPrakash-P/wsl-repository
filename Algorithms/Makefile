#SRCFILES:=$(wildcard *.cpp)
SRCFILES:=$(shell find . -name '*.cpp')
SRCDIRS:=$(patsubst %/,%,$(dir $(wildcard */)))
OBJFILES:=$(SRCFILES:.cpp = .o)
TARGETS:=$(basename $(SRCFILES))
#SRCDIRS:=$(basename $(SRCFILES))

.PHONY: print BubbleSort

print:
	$(info Making target $@)
	$(info $$SRCFILES = $(SRCFILES))
	$(info $$OBJFILES = $(OBJFILES))
	$(info $$TARGETS = $(TARGETS))
	$(info $$SRCDIRS = $(SRCDIRS))
	$(info $$CXX = $(CXX))

all:$(TARGETS)
	$(info Making target $@)

BubbleSort:
	$(info Making specific target $@)
	$(CXX) $@/$@.cpp -static -o ./$@/lib$@.so

%:
	$(info Making target $@)
	$(CXX) $@.cpp -o $@
