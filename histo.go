package histo

func Histo(x []uint8, v []float32, n_f uint64, n_r uint64, nb uint64, out []float32) {
	n_r_2 := n_r / 2

	for f := uint64(0); f < n_f; f++ {
		x_f := x[n_r_2*f:]
		f_f := v[n_r*f:]
		out_f := out[nb*f:]
		for i := uint64(0); i < n_r_2; i++ {
			out_f[x_f[i]&0x0f] += f_f[i*2]
			out_f[(x_f[i] >> 4)] += f_f[i*2+1]
		}
	}
}
