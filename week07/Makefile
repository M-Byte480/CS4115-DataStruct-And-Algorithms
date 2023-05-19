#
# 
# Makefile  for CS4815 lab 
#
# Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
# 


NAME=matz
LIBS=
SOURCES=\
	matz.cc\


CC=gcc
CFLAGS=

CXX=g++
CXXFLAGS=$(CFLAGS)

LD=g++
LDFLAGS=


OBJECTS=${SOURCES:.cc=.o}


.PHONY: clean
.SUFFIXES: .o .c .cc .cpp


all: program

clean:
	$(RM) $(OBJECTS)
	$(RM) $(NAME)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<


program: $(NAME)
$(NAME): $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^

