TARGET := WSLTestNormal
TARGET_NOSTART := WSLTestNoStartFiles

SRCFILES := $(shell find . -name main.cpp)
SRCFILES_NOSTART := $(shell find . -name main_nostartfiles.cpp)
CXXFLAGS_NOSTART := -nostartfiles
CXXFLAGS += -Wfatal-errors -fpermissive

OBJFILES:=$(SRCFILES:.cpp=.o)
OBJFILES_NOSTART:=$(SRCFILES_NOSTART:.cpp=.o)

all : $(TARGET) $(TARGET_NOSTART)
	@echo Inside all
	@echo TARGET   = $(TARGET)
	@echo SRCFILES = $(SRCFILES)
	@echo OBJFILES = $(OBJFILES)
	@echo TARGET_NOSTART   = $(TARGET_NOSTART)
	@echo SRCFILES_NOSTART = $(SRCFILES_NOSTART)
	@echo OBJFILES_NOSTART = $(OBJFILES_NOSTART)
	$(RM) *.o

$(TARGET) : $(OBJFILES)
	@echo Making $(TARGET) from $(OBJFILES)...
	#@echo $$^            = $^#FIRST Prerequisite
	#@echo DollarAT       = $@#File name of the target of the rule.
	#@echo Dollar<        = $<#FIRST Prerequisite ONLY
	#@echo Dollar?        = $?#ALL Prerequisite newer than target
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) -lpthread

$(TARGET_NOSTART) : $(OBJFILES_NOSTART)
	@echo Making $(TARGET_NOSTART) from $(OBJFILES_NOSTART)...
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_NOSTART) -o $(TARGET_NOSTART) $(OBJFILES_NOSTART)

%.o : %.cpp
	@echo "COMPILING SOURCE $< INTO OBJECT $@"
	$(CXX) -c $(CXXFLAGS) $< -o $@
	@echo CREATING OBJECTS

clean:
	$(RM) *.o $(TARGET) $(TARGET_NOSTART)
