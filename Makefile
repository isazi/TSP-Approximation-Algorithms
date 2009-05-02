
CC=g++
CFLAGS=-O2 -march=core2 -Wall -ansi -pipe -fomit-frame-pointer
INCLUDE=-I"/home/isazi/Code/C++/TSP_approx_algorithms/include"
LIBS=-lrt
ARGUMENT=lib/ArgumentList.o
BLOSSOMV=lib/misc.o lib/PMduals.o lib/PMexpand.o lib/PMinit.o lib/PMinterface.o lib/PMmain.o lib/PMrepair.o lib/PMshrink.o lib/MinCost.o

all: generatore_grafi doubleMST refinedDoubleMST christofides cycleCover distribuzionePesi betaMetricita

generatore_grafi: generatore_grafi.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/generatore_grafi generatore_grafi.cpp $(ARGUMENT)

doubleMST: doubleMST.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/doubleMST doubleMST.cpp $(ARGUMENT)

refinedDoubleMST: refinedDoubleMST.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/refinedDoubleMST refinedDoubleMST.cpp $(ARGUMENT)

christofides: christofides.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/christofides christofides.cpp $(BLOSSOMV) $(LIBS) $(ARGUMENT)
	
cycleCover: cycleCover.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/cycleCover cycleCover.cpp $(BLOSSOMV) $(LIBS) $(ARGUMENT)

distribuzionePesi: distribuzionePesi.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/distribuzionePesi distribuzionePesi.cpp $(ARGUMENT)

betaMetricita: betaMetricita.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o bin/betaMetricita betaMetricita.cpp $(ARGUMENT)

clean:
	rm bin/generatore_grafi
	rm bin/doubleMST
	rm bin/refinedDoubleMST
	rm bin/christofides
	rm bin/cycleCover
	rm bin/distribuzionePesi
	rm bin/betaMetricita
