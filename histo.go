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

const gl = 8

func Histo8(x []uint8, v []float32, n_f uint64, n_r uint64, nb uint64, out []float32) {
	n_r_2 := n_r / 2
	gc := n_r_2 / gl

	for f := uint64(0); f < n_f; f++ {
		x_f := x[n_r_2*f:]
		f_f := v[n_r*f:]
		out_f := out[nb*f:]
		var xs [8]uint8
		for i := uint64(0); i < gc; i++ {
			xi := i * gl

			xs[0] = x_f[xi+0]
			xs[1] = x_f[xi+1]
			xs[2] = x_f[xi+2]
			xs[3] = x_f[xi+3]
			xs[4] = x_f[xi+4]
			xs[5] = x_f[xi+5]
			xs[6] = x_f[xi+6]
			xs[7] = x_f[xi+7]

			out_f[xs[0]&0x0f] += f_f[xi*2+0*2]
			out_f[xs[1]&0x0f] += f_f[xi*2+1*2]
			out_f[xs[2]&0x0f] += f_f[xi*2+2*2]
			out_f[xs[3]&0x0f] += f_f[xi*2+3*2]
			out_f[xs[4]&0x0f] += f_f[xi*2+4*2]
			out_f[xs[5]&0x0f] += f_f[xi*2+5*2]
			out_f[xs[6]&0x0f] += f_f[xi*2+6*2]
			out_f[xs[7]&0x0f] += f_f[xi*2+7*2]

			out_f[(xs[0] >> 4)] += f_f[xi*2+0*2+1]
			out_f[(xs[1] >> 4)] += f_f[xi*2+1*2+1]
			out_f[(xs[2] >> 4)] += f_f[xi*2+2*2+1]
			out_f[(xs[3] >> 4)] += f_f[xi*2+3*2+1]
			out_f[(xs[4] >> 4)] += f_f[xi*2+4*2+1]
			out_f[(xs[5] >> 4)] += f_f[xi*2+5*2+1]
			out_f[(xs[6] >> 4)] += f_f[xi*2+6*2+1]
			out_f[(xs[7] >> 4)] += f_f[xi*2+7*2+1]
		}

		for i := gl * gc; i < n_r_2; i++ {
			out_f[x_f[i]&0x0f] += f_f[i*2]
			out_f[(x_f[i] >> 4)] += f_f[i*2+1]
		}
	}
}
