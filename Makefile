CXX = g++

CXXFLAGS = -Wall -std=c++11

SRCS = main.cpp receipt.cpp schrift.cpp

OBJS = main.o receipt.o schrift.o

EXEC = program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

main.o: main.cpp receipt.h
	$(CXX) $(CXXFLAGS) -c main.cpp

receipt.o: receipt.cpp receipt.h
	$(CXX) $(CXXFLAGS) -c receipt.cpp

clean:
	rm -f $(OBJS) $(EXEC)
