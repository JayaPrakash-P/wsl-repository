
TARGET := WSLTest

SRCFILES:=$(shell find . -name *.cpp)
OBJFILES:=$(SRCFILES:.cpp=.o)

all : $(TARGET)
	@echo  MAKING ALL
	@echo SRCFILES = $(SRCFILES)
	@echo OBJFILES = $(OBJFILES)
	@echo TARGET = $(TARGET)

$(TARGET) : $(OBJFILES)
	@echo SRCFILES = $(SRCFILES)
	@echo OBJFILES = $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

#%.o : %.cpp
#	@echo "COMPILING SOURCE $< INTO OBJECT $@"
#	$(CXX) -c $(CXXFLAGS) $< -o $@
#	@echo CREATING OBJECTS

clean:
	$(RM) *.o $(TARGET)
