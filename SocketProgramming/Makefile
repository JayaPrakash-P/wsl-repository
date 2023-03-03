CXX := clang++

SRCS     := $(wildcard *.cc)
OBJS     := $(SRCS:cc=o)
TARGETS  := $(basename $(SRCS))
CXXFLAGS := -std=c++17 -g -Wall
LDFLAGS  := -pthread

#Clean is executed even if a file named clean exists
.PHONY: clean

print:
	$(info SRCS = $(SRCS))
	$(info OBJS = $(OBJS))
	$(info TARGETS = $(TARGETS))


all: $(TARGETS) $(OBJS)
	$(info Building $@ from $^)
	rm -rf *.o

%:%.o
	$(info Building $@ from $<)
	$(CXX) $(LDFLAGS) $< -o $@

%.o:%.cc
	$(info Building $@ from $<)
	$(CXX) -c $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(TARGETS)
	rm -rf *.o
