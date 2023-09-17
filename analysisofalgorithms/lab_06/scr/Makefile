#main.o: main.cpp
#	g++ -c main.cpp

#main.exe: main.o
#	g++ -o main.exe

#main.exe: main.cpp matrix.cpp matrix.h
#    g++ -o main.cpp matrix.cpp

#clean:
#	rm -f *.o *.exe 

output: main.o matrix.o CompleteBust.o array.o AntAlgorithm.o
		g++ main.o matrix.o CompleteBust.o array.o AntAlgorithm.o -o output

main.o: main.cpp
		g++ -c main.cpp

matrix.o: matrix.cpp
		g++ -c matrix.cpp

CompleteBust.o: CompleteBust.cpp
		g++ -c CompleteBust.cpp

array.o: array.cpp
		g++ -c array.cpp	

AntAlgorithm.o: AntAlgorithm.cpp
		g++ -c AntAlgorithm.cpp			

clean:
		rm *.o 