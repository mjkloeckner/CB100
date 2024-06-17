CC := g++
CFLAGS := -Wall -pedantic -ansi -std=c++98 -O3
SRCS := $(wildcard *.cpp)
LIBS := $(wildcard *.h)

TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
