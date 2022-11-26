CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

Project: Main.o  
	$(CC) $(CFLAGS) -o Project Main.o 

Main.o: Main.cpp Stocks.h
	$(CC) $(CFLAGS) -c Main.cpp
	

clean:
	rm -rf  Project *.o
