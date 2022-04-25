package main

import (
	"fmt"
	"time"
)

func printMatrix(m [][]float64) {
	for i := 0; i < len(m); i++ {
		fmt.Printf("[%6.2g", m[i][0])

		for j := 1; j < len(m[i]); j++ {
			fmt.Printf(" %6.2g", m[i][j])
		}

		fmt.Println("]")
	}
}

func main() {
	const n_routines = 3

	A := [][]float64{
		{1.8, 2.6, 5.7, 1.1},
		{3.7, 4.1, 10.2, 9.9},
		{8.9, 7.9, 9.6, 8.8},
		{4.4, 5.5, 6.6, 7.7},
	}
	b := []float64{1, 1, 1, 2}

	const runs = 10000

	start := time.Now()
	var s [][]float64
	for i := 0; i < runs; i++ {
		s = sequentialGauss(A, b)
	}
	s_time := time.Since(start)

	start = time.Now()
	var p [][]float64
	for i := 0; i < runs; i++ {
		p = parallelGauss(A, b, n_routines)
	}
	p_time := time.Since(start)

	printMatrix(s)
	fmt.Println(s_time)
	printMatrix(p)
	fmt.Println(p_time)
}
