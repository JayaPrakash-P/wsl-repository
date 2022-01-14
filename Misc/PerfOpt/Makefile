
CXX         := g++
#CXXFLAGS    := -g -std=c++17 -fno-elide-constructors
#LDFLAGS     :=  -ltbb -pthread
SRCFILES    := $(wildcard *.cpp)
OBJFILES    := $(SRCFILES:.cpp=.o)
TGTFILES    := $(basename $(SRCFILES))

print:
	$(info SRCFILES = $(SRCFILES) )
	$(info OBJFILES = $(OBJFILES) )
	$(info TGTFILES = $(TGTFILES) )

all:$(TGTFILES)
	rm -rf $(OBJFILES)

%:%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $@.cpp -o $@
    
run:$(TGTFILES)
	./Run.sh $^

compiler:$(SRCFILES)
	g++ -S $< -O1 -o $(basename $<).s
    
clean:
	rm -rf $(OBJFILES) $(TGTFILES)