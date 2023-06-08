package histo

import (
	"fmt"
	"testing"
)

func setup(n_f, n_r, nb uint64) ([]uint8, []float32, []float32) {
	x := make([]uint8, n_f*n_r/2)
	f := make([]float32, n_f*n_r)
	out := make([]float32, n_f*nb)

	return x, f, out
}

func BenchmarkHisto(b *testing.B) {
	var n_f uint64 = 30
	var nb uint64 = 16

	for _, n_r := range []uint64{1_000_000, 10_000_000, 100_000_000} {
		x, f, _ := setup(n_f, n_r, nb)
		b.Run(fmt.Sprintf("%d", n_r), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				out := make([]float32, n_f*nb)
				Histo(x, f, n_f, n_r, nb, out)
			}
		})
	}
}

func BenchmarkHisto8(b *testing.B) {
	var n_f uint64 = 30
	var nb uint64 = 16

	for _, n_r := range []uint64{1_000_000, 10_000_000, 100_000_000} {
		x, f, _ := setup(n_f, n_r, nb)
		b.Run(fmt.Sprintf("%d", n_r), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				out := make([]float32, n_f*nb)
				Histo8(x, f, n_f, n_r, nb, out)
			}
		})
	}
}
