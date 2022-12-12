CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl

Project: Main.o ReadLoadData.o Stocks.o
	$(CC) $(CFLAGS) -o Project Main.o ReadLoadData.o Stocks.o

Main.o: Stocks.h ReadLoadData.h Main.cpp
	$(CC) $(CFLAGS) -c Main.cpp
	
ReadLoadData.o: Stocks.h ReadLoadData.h ReadLoadData.cpp 
	$(CC) $(CFLAGS) -c ReadLoadData.cpp
	
Stocks.o: Stocks.h Stocks.cpp
	$(CC) $(CFLAGS) -c Stocks.cpp

clean:
	rm -rf  Project *.o
