CXX = g++
CPPFLAGS = -g -Wall

stringparser: stringparser.cpp stackstr.o lliststr.o
	$(CXX) $(CPPFLAGS) $^ -o stringparser

stackstr.o: stackstr.h stackstr.cpp lliststr.o
	$(CXX) $(CPPFLAGS) -c stackstr.cpp -o stackstr.o

lliststr.o: lliststr.h lliststr.cpp
	$(CXX) $(CPPFLAGS) -c lliststr.cpp -o lliststr.o

.PHONY: clean

clean:
	rm -rf *.o stringparser