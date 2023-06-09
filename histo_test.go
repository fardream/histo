package histo

import (
	"fmt"
	"math"
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

func makexy(n uint64) ([]float32, []float32) {
	return make([]float32, n), make([]float32, n)
}

func BenchmarkDot(b *testing.B) {
	for _, n := range []uint64{1_000_000, 10_000_000, 100_000_000} {
		x, y := makexy(n)
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				Dot(x, y, n)
			}
		})
	}
}

func BenchmarkDot8(b *testing.B) {
	for _, n := range []uint64{1_000_000, 10_000_000, 100_000_000} {
		x, y := makexy(n)
		b.Run(fmt.Sprintf("%d", n), func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				Dot8(x, y, n)
			}
		})
	}
}

func BenchmarkExp8(b *testing.B) {
	for k := 0; k < b.N; k++ {
		for i := -10.; i < 10.; i += 0.01 {
			i := float32(i)
			vals := []float32{
				i + 0,
				i + 1,
				i + 2,
				i + 3,
				i + 4,
				i + 5,
				i + 6,
				i + 7,
			}
			outs := make([]float32, 8)
			Exp8(vals, outs)

			realout := math.Exp(float64(i))

			if float32(realout) != outs[0] {
				b.Fatalf("failed to calc: %f vs %f", realout, outs[0])
			}

		}
	}
}
