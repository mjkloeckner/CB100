CC := g++
CFLAGS := -Wall -Wshadow -pedantic -ansi -std=c++98 -O3
SRCS := $(wildcard *.cpp)
LIBS := $(wildcard *.hpp)

TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) $(LIBS)
	$(CC) $(CLIBS) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
