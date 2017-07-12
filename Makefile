CC=g++
CCFlAGS=-c -Wall

SRC_DIR=src
OUTPUT_DIR=bin

SRCS=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(SRCS:.cpp=.o)

.PHONY: clean

all: $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(OUTPUT_DIR)/Mandelbrot

.cpp.o:
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf bin/*
