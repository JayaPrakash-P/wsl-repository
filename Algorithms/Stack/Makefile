SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

CXX       := g++
CXX_FLAGS := -g
TARGET    := StackTest

all : $(TARGET)
	$(info Making $@ with $^)

$(TARGET) : $(OBJS)
	$(info Making $@ with $^)
	$(CXX) $(CXX_FLAGS) $^ -o $@

%.o:%.cpp
	$(CXX) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
