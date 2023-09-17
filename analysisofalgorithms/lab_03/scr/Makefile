output: main.o array.o 
		g++ main.o array.o -o output

output_test: main_test.o array.o getCPUTime.o
		g++ main_test.o array.o getCPUTime.o -o output_test

main_test.o: main_test.cpp
		g++ -c main_test.cpp		

main.o: main.cpp
		g++ -c main.cpp

array.o: array.cpp
		g++ -c array.cpp

processTime.o: processTime.cpp
		g++ -c processTime.cpp	

getCPUTime.o: getCPUTime.cpp
		g++ -c getCPUTime.cpp			

clean:
		rm *.o 