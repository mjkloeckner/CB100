CC := g++
CFLAGS := -Wall -pedantic -ansi -std=c++98 -O3
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f $(OBJS)

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
