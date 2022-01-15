CXX      := g++
LD_FLAGS := -pthread
TARGET   := ThreadPool

OBJDIR     = obj

SOURCES := $(wildcard *.cpp)
OBJECTS := $(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))

$(info $$SOURCES is [$(SOURCES)])
$(info $$OBJECTS is [$(OBJECTS)])

print:
	$(info $$SOURCES is [$(SOURCES)])
	$(info $$OBJECTS is [$(OBJECTS)])
    
all:$(TARGET)
	
$(TARGET):$(OBJECTS)
	$(CXX) -g $(LD_FLAGS) $^ -o $@

$(OBJDIR)/%.o:%.cpp
	$(CXX) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)