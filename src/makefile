CC = g++
CPPFLAGS = -g -std=c++11 -stdlib=libc++ -Wall

#SRCS=$(wildcard *.cpp)
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)

default:main
main:$(OBJS)

clean:
	$(RM) main *.o
