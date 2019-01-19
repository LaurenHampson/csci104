# Let's declare some variables

CC       = g++

CPPFLAGS = -Wall -g

BIN_DIR  = bin

GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread


search: search.cpp querysearch.cpp lowercase.cpp webpage.cpp parser.cpp querysearch.h parser.h webpage.h 

	$(CC) $(CPPFLAGS)  -std=c++11 $^ -o $@

crawler: crawler.cpp 

	$(CC) $(CPPFLAGS)  -std=c++11 $^ -o $@

clear:
	
	rm crawler
	rm search