TARGET		= DesignPatternTest

CC			= gcc
CXX			= g++
RM			= rm -f
CPPFLAGS	= -g -I./Singleton

#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)

SRCS=DesignPatternTest.cc

OBJS=$(subst .cc,.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) $@
	$(CXX) $(CPPFLAGS) -MM $^ >> $@;

clean:
	$(RM) $(OBJS) DesignPatternTest

distclean: clean
	$(RM) *~ .depend

include .depend