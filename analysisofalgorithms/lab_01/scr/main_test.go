package main

import "testing"

func BenchmarkRecursiveLen5(b *testing.B) {
	fWord := "about"
	sWord := "above"

	for i := 0; i < b.N; i++ {
		Recursive(fWord, sWord)
	}
}

func BenchmarkRecursiveLen10(b *testing.B) {
	fWord := "abbanition"
	sWord := "abaptiston"

	for i := 0; i < b.N; i++ {
		Recursive(fWord, sWord)
	}
}

func BenchmarkRecursiveLen15(b *testing.B) {
	fWord := "characteristics"
	sWord := "recommendations"

	for i := 0; i < b.N; i++ {
		Recursive(fWord, sWord)
	}
}

// RecursiveMatrix method becnhmarks.

func BenchmarkRecursiveMatrixLen10(b *testing.B) {
	fWord := "abbanition"
	sWord := "abaptiston"

	for i := 0; i < b.N; i++ {
		RecursiveMatrix(fWord, sWord)
	}
}

func BenchmarkRecursiveMatrixLen20(b *testing.B) {
	fWord := "abdominohysterectomy"
	sWord := "acetylcholinesterase"

	for i := 0; i < b.N; i++ {
		RecursiveMatrix(fWord, sWord)
	}
}
func BenchmarkRecursiveMatrixLen30(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrile"
	sWord := "abdominalexternalobliquemuscle"

	for i := 0; i < b.N; i++ {
		RecursiveMatrix(fWord, sWord)
	}
}

func BenchmarkRecursiveMatrixLen50(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		RecursiveMatrix(fWord, sWord)
	}
}

func BenchmarkRecursiveMatrixLen100(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		RecursiveMatrix(fWord, sWord)
	}
}

func BenchmarkRecursiveMatrixLen200(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		RecursiveMatrix(fWord, sWord)
	}
}

// IterativeMatrix method benchmarks.

func BenchmarkIterativeMatrixLen10(b *testing.B) {
	fWord := "abbanition"
	sWord := "abaptiston"

	for i := 0; i < b.N; i++ {
		IterativeMatrix(fWord, sWord)
	}
}

func BenchmarkIterativeMatrixLen20(b *testing.B) {
	fWord := "abdominohysterectomy"
	sWord := "acetylcholinesterase"

	for i := 0; i < b.N; i++ {
		IterativeMatrix(fWord, sWord)
	}
}

func BenchmarkIterativeMatrixLen30(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrile"
	sWord := "abdominalexternalobliquemuscle"

	for i := 0; i < b.N; i++ {
		IterativeMatrix(fWord, sWord)
	}
}

func BenchmarkIterativeMatrixLen50(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		IterativeMatrix(fWord, sWord)
	}
}

func BenchmarkIterativeMatrixLen100(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		IterativeMatrix(fWord, sWord)
	}
}

func BenchmarkIterativeMatrixLen200(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		IterativeMatrix(fWord, sWord)
	}
}

// DamerauLevenshtein method benchmarks.

func BenchmarkDamerauLevenshteinLen10(b *testing.B) {
	fWord := "abbanition"
	sWord := "abaptiston"

	for i := 0; i < b.N; i++ {
		DamerauLevenshtein(fWord, sWord)
	}
}

func BenchmarkDamerauLevenshteinLen20(b *testing.B) {
	fWord := "abdominohysterectomy"
	sWord := "acetylcholinesterase"

	for i := 0; i < b.N; i++ {
		DamerauLevenshtein(fWord, sWord)
	}
}

func BenchmarkDamerauLevenshteinLen30(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrile"
	sWord := "abdominalexternalobliquemuscle"

	for i := 0; i < b.N; i++ {
		DamerauLevenshtein(fWord, sWord)
	}
}

func BenchmarkDamerauLevenshteinLen50(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		DamerauLevenshtein(fWord, sWord)
	}
}

func BenchmarkDamerauLevenshteinLen100(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		DamerauLevenshtein(fWord, sWord)
	}
}

func BenchmarkDamerauLevenshteinLen200(b *testing.B) {
	fWord := "chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy" +
		"chlorobenzylidenemalononitrileabdominohysterectomy"
	sWord := "abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase" +
		"abdominalexternalobliquemuscleacetylcholinesterase"

	for i := 0; i < b.N; i++ {
		DamerauLevenshtein(fWord, sWord)
	}
}

// import (
// 	"fmt"

// 	"github.com/logrusorgru/aurora"
// )

// func main() {
// 	fmt.Println(aurora.Magenta("Расстояние Левенштейна\n"))

// 	fmt.Printf("Введите первое слово: ")
// 	firstWord := ReadWord()

// 	fmt.Printf("Введите второе слово: ")
// 	secondWord := ReadWord()

// 	distanceRecursive := Recursive(firstWord, secondWord)
// 	fmt.Println(aurora.Magenta("Рекурсивный метод без заполнения матрицы:\n"))
// 	fmt.Printf("Расстояние: %d\n\n", aurora.Green(distanceRecursive))

// }

// func ReadWord() string {
// 	var word string
// 	fmt.Scanln(&word)

// 	return word
// }

// //===============================================================
// func Recursive(firstWord, secondWord string) int {
// 	firstWordRune, secondWordRude := []rune(firstWord), []rune(secondWord)
// 	firstLen, secondLen := len(firstWordRune), len(secondWordRude)

// 	return GetDistance(firstWordRune, secondWordRude, firstLen, secondLen)
// }

// func GetDistance(firstWord, secondWord []rune, i, j int) int {
// 	if (i * j) == 0 {
// 		return i + j
// 	}
// 	weight := 1
// 	if firstWord[i-1] == secondWord[j-1] {
// 		weight = 0
// 	}
// 	return min(GetDistance(firstWord, secondWord, i, j-1)+1,
// 		GetDistance(firstWord, secondWord, i-1, j)+1,
// 		GetDistance(firstWord, secondWord, i-1, j-1)+weight)
// }

// //===============================================================

// func RecursiveMatrix(firstWord, secondWord string) int {
// 	firstWordRune, secondWordRude := []rune(firstWord), []rune(secondWord)
// 	firstLen, secondLen := len(firstWordRune), len(secondWordRude)

// }

// func min(values ...int) int {
// 	var m = values[0]
// 	for _, v := range values {
// 		if v < m {
// 			m = v
// 		}
// 	}
// 	return m
// }
