package main

func sequentialUpperTriangle(m [][]float64) {
	for row := 0; row < len(m); row++ {
		for col := 0; col < row; col++ {
			reduceRow(m, row, col)
		}

		normalizeRow(m, row)
	}
}

func sequentialGauss(A [][]float64, b []float64) [][]float64 {
	m := make([][]float64, len(A))

	for i := 0; i < len(m); i++ {
		m[i] = append(A[i], b[i])
	}

	sequentialUpperTriangle(m)

	return m
}
