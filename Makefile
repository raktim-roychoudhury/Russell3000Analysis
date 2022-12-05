CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

Project: Main.o  
	$(CC) $(CFLAGS) -o Project Main.o ReadLoadData.o bootstrap.o

Main.o: Main.cpp Stocks.h
	$(CC) $(CFLAGS) -c Main.cpp
	
ReadLoadData.o: ReadLoadData.cpp Stocks.h
	$(CC) $(CFLAGS) -c ReadLoadData.cpp
	
bootstrap.o: Stocks.h bootstrap.h
	$(CC) $(CFLAGS) -c bootstrap.cpp

clean:
	rm -rf  Project *.o
