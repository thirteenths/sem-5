#main.o: main.cpp
#	g++ -c main.cpp

#main.exe: main.o
#	g++ -o main.exe

#main.exe: main.cpp matrix.cpp matrix.h
#    g++ -o main.cpp matrix.cpp

#clean:
#	rm -f *.o *.exe 

output: main.o matrix.o
		g++ main.o matrix.o -o output

main.o: main.cpp
		g++ -c main.cpp

matrix.o: matrix.cpp
		g++ -c matrix.cpp

clean:
		rm *.o *.exe output