TARGET := WSLTest

SRCFILES:=$(shell find . -name *.cpp)
OBJFILES:=$(SRCFILES:.cpp=.o)

all : $(TARGET)
	@echo Inside all
	@echo TARGET   = $(TARGET)
	@echo SRCFILES = $(SRCFILES)
	@echo OBJFILES = $(OBJFILES)

$(TARGET) : $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

#%.o : %.cpp
#	@echo "COMPILING SOURCE $< INTO OBJECT $@"
#	$(CXX) -c $(CXXFLAGS) $< -o $@
#	@echo CREATING OBJECTS

clean:
	$(RM) *.o $(TARGET)
