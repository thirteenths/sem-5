output.out: main.o levenshtein.o
	g++ main.o levenshtein.o -o output.out

levenshtein.o: levenshtein.cpp
	g++ -c levenshtein.cpp

main.o: main.cpp
		g++ -c main.cpp

clean:
		rm *.o 