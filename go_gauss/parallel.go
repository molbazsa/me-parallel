package main

import "sync"

func reduceRow(m [][]float64, row int, col int) {
	scalar := -m[row][col]

	for i := 0; i < len(m[row]); i++ {
		m[row][i] += scalar * m[col][i]
	}
}

func normalizeRow(m [][]float64, row int) {
	divisor := m[row][row]

	for i := 0; i < len(m[row]); i++ {
		m[row][i] /= divisor
	}
}

func parallelUpperTriangle(m [][]float64, n_routines int) {
	var wg sync.WaitGroup
	var done []chan int

	for i := 0; i < n_routines; i++ {
		done = append(done, make(chan int, n_routines-1))
	}

	for i := 0; i < n_routines; i++ {
		wg.Add(1)
		id := i

		go func() {
			defer wg.Done()

			for row := id; row < len(m); row += n_routines {
				valid := row - n_routines + 1

				if valid < 0 {
					valid = 0
				}

				for col := 0; col < valid; col++ {
					reduceRow(m, row, col)
				}

				for r := 0; r < row-valid; r++ {
					col := <-done[id]
					reduceRow(m, row, col)
				}

				normalizeRow(m, row)

				for r := 0; r < n_routines; r++ {
					if r != id {
						done[r] <- row
					}
				}
			}
		}()
	}

	wg.Wait()
}

func parallelGauss(A [][]float64, b []float64, n_routines int) [][]float64 {
	m := make([][]float64, len(A))

	for i := 0; i < len(m); i++ {
		m[i] = append(A[i], b[i])
	}

	parallelUpperTriangle(m, n_routines)

	return m
}
