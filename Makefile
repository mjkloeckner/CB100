CC := g++
CFLAGS := -Wall -Wshadow -pedantic -ansi -std=c++98 -O3
SRCS := $(wildcard *.cpp)

TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CLIBS) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
