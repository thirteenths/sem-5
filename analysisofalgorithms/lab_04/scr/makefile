output.out: main.o matrix.o getCPUTime.o
	g++ -std=c++11 -pthread -fopenmp main.o matrix.o getCPUTime.o -o output.out

main.o: main.cpp
		g++ -c main.cpp

matrix.o: matrix.cpp
		g++ -c matrix.cpp		

getCPUTime.o: getCPUTime.cpp
		g++ -c getCPUTime.cpp		

clean:
		rm *.o 