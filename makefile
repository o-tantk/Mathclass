CXX=g++
CXXFLAGS=-g -std=c++11 -stdlib=libc++ -Wall

SRCDIR=src
TARGET=tfm

#SRCS=$(wildcard $(SRCDIR)/*.cpp)
SRCS=$(SRCDIR)/main.cpp
OBJS=$(SRCS:.cpp=.o)

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJS)
