GCC=g++
COMPILERFLAGS=-Wall -Iinclude
LINKERFLAGS=-lglut -lGLU -lGL
SRCFILES:=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCFILES))
BINARY=fishtank

default: all

%.o: %.cpp
	$(GCC) $(COMPILERFLAGS) -c -o $@ $<

all: $(OBJS)
	$(GCC) -o $(BINARY) $(OBJS) $(LINKERFLAGS) 

clean:
	-rm -f $(OBJS) $(BINARY)

