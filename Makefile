CXX = g++

CPPFLAGS = -g -Wall


LengthMismatch: LengthMismatch.h LengthMismatch.cpp

	$(CXX) $(CPPFLAGS) $^ -c


functor: functor.h functor.cpp

	$(CXX) $(CPPFLAGS) $^ -c

Thanksgiving: Thanksgiving.cpp LengthMismatch.h LengthMismatch.cpp

	$(CXX) $(CPPFLAGS) $^ -c 


.PHONY: clean



clean:

	rm -rf *.o LengthMismatch
	rm -rf *.o functor
	rm -rf *.o Thanksgiving