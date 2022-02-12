CC := cc
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

TARGET := LinkageTest

print:clean
	$(info $$SRCS   = $(SRCS))
	$(info $$OBJS   = $(OBJS))
	$(info $$TARGET = $(TARGET))

all: clean $(TARGET)
	$(info Making target = $@)

$(TARGET) : $(OBJS)
	$(info Making target = $@ with $^)
	$(CC) $^ -o $@
	rm -rf $(OBJS)

%.o : %.c
	$(info Making target = $@ with $<)
	$(CC) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)