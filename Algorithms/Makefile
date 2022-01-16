SRCFILES	:=$(wildcard *.cpp)
OBJFILES	:=$(SRCFILES:.cpp=.o)
TARGETS		:=$(basename $(SRCFILES))
GTEST_FLAGS :=-lgtest -lgtest_main -pthread

.PHONY: print BubbleSort all

print:
	$(info Making target $@)
	$(info $$SRCFILES = $(SRCFILES))
	$(info $$OBJFILES = $(OBJFILES))
	$(info $$TARGETS = $(TARGETS))
	$(info $$CXX = $(CXX))

all:$(TARGETS)
	$(info Making target $@)

% : %.o
	$(info Making target $@)
	$(CXX) $@.o $(GTEST_FLAGS) -o $@

%.o : %.cpp
	$(info Making target $@)
	$(CXX) -c $^ -o $@

clean:
	$(info Making target $@)
	rm -rf $(OBJFILES) $(TARGETS)