
CC=g++
CFLAGS=-O0 -Wall -g -ansi
INCLUDE=-I"/home/isazi/Code/C++/TSP_approx_algorithms/include"
ARGUMENT=../lib/ArgumentList.o

all: GrafoNonOrientatoBetaMetrico_ListaArchiTest TSPInstanceTest TSPReaderTest TSPWriterTest verifyBetaMetricTest getArcoCompresoTest spostamentoMetricoTest SpaceGenerator generatoreSperimentale

GrafoNonOrientatoBetaMetrico_ListaArchiTest:
	$(CC) $(CFLAGS) $(INCLUDE) -o GrafoNonOrientatoBetaMetrico_ListaArchiTest GrafoNonOrientatoBetaMetrico_ListaArchiTest.cpp
	
TSPInstanceTest:
	$(CC) $(CFLAGS) $(INCLUDE) -o TSPInstanceTest TSPInstanceTest.cpp

TSPReaderTest:
	$(CC) $(CFLAGS) $(INCLUDE) -o TSPReaderTest TSPReaderTest.cpp

TSPWriterTest:
	$(CC) $(CFLAGS) $(INCLUDE) -o TSPWriterTest TSPWriterTest.cpp
	
tsp_approssimatoTest:
	$(CC) $(CFLAGS) $(INCLUDE) -o tsp_approssimatoTest tsp_approssimatoTest.cpp
	
verifyBetaMetricTest:
	$(CC) $(CFLAGS) $(INCLUDE) -o verifyBetaMetricTest verifyBetaMetricTest.cpp

getArcoCompresoTest:
	$(CC) $(CFLAGS) $(INCLUDE) -o getArcoCompresoTest getArcoCompresoTest.cpp

spostamentoMetricoTest: spostamentoMetricoTest.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o spostamentoMetricoTest spostamentoMetricoTest.cpp

SpaceGenerator: SpaceGenerator.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o SpaceGenerator SpaceGenerator.cpp -lm
	
generatoreSperimentale: generatoreSperimentale.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o generatoreSperimentale generatoreSperimentale.cpp ${ARGUMENT}

clean:
	rm GrafoNonOrientatoBetaMetrico_ListaArchiTest
	rm TSPInstanceTest
	rm TSPReaderTest
	rm TSPWriterTest
	rm tsp_approssimatoTest
	rm verifyBetaMetricTest
	rm getArcoCompresoTest
	rm spostamentoMetricoTest
	rm SpaceGenerator
	rm generatoreSperimentale
