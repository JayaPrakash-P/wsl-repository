CXX      := g++
LD_FLAGS := -pthread
TARGET   := ThreadPool

INCLUDEDIR = ./include
SOURCEDIR  = ./src
OBJDIR     = ./obj

SOURCES := $(notdir $(shell find $(SOURCEDIR) -name '*.cpp'))
OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:%.cpp=%.o))

$(info $$SOURCES is [$(SOURCES)])
$(info $$OBJECTS is [$(OBJECTS)])

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CXX) -g $(LD_FLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o:$(SOURCEDIR)/%.cpp
	$(CXX) -c -I$(INCLUDEDIR) $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)