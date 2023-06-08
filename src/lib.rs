pub fn histo(x: &[u8], v: &[f32], n_f: usize, n_r: usize, nb: usize, out: &mut [f32]) {
    let n_r_2 = n_r / 2;
    for f in 0..n_f {
        let x_f = &x[(n_r_2 * f)..(f * n_r_2 + n_r_2)];
        let f_f = &v[(n_r * f)..(n_r * f + n_r)];
        let out_f = &mut out[(nb * f)..(nb * f + nb)];
        for i in 0..n_r_2 {
            out_f[(x_f[i] & 0x0f) as usize] += f_f[i * 2];
            out_f[(x_f[i] >> 4) as usize] += f_f[i * 2 + 1];
        }
    }
}

pub fn histo8(x: &[u8], v: &[f32], n_f: usize, n_r: usize, nb: usize, out: &mut [f32]) {
    let n_r_2 = n_r / 2;
    const GL: usize = 8;
    let gc = n_r_2 / GL;

    for f in 0..n_f {
        let x_f = &x[(n_r_2 * f)..(f * n_r_2 + n_r_2)];
        let f_f = &v[(n_r * f)..(n_r * f + n_r)];
        let out_f = &mut out[(nb * f)..(nb * f + nb)];
        let mut xs: [u8; 8] = [0; 8];
        for i in 0..gc {
            let xi = i * GL;
            xs[0] = x_f[xi + 0];
            xs[1] = x_f[xi + 1];
            xs[2] = x_f[xi + 2];
            xs[3] = x_f[xi + 3];
            xs[4] = x_f[xi + 4];
            xs[5] = x_f[xi + 5];
            xs[6] = x_f[xi + 6];
            xs[7] = x_f[xi + 7];

            out_f[(xs[0] & 0x0f) as usize] += f_f[xi * 2 + 0 * 2];
            out_f[(xs[1] & 0x0f) as usize] += f_f[xi * 2 + 1 * 2];
            out_f[(xs[2] & 0x0f) as usize] += f_f[xi * 2 + 2 * 2];
            out_f[(xs[3] & 0x0f) as usize] += f_f[xi * 2 + 3 * 2];
            out_f[(xs[4] & 0x0f) as usize] += f_f[xi * 2 + 4 * 2];
            out_f[(xs[5] & 0x0f) as usize] += f_f[xi * 2 + 5 * 2];
            out_f[(xs[6] & 0x0f) as usize] += f_f[xi * 2 + 6 * 2];
            out_f[(xs[7] & 0x0f) as usize] += f_f[xi * 2 + 7 * 2];
            out_f[(xs[0] >> 4) as usize] += f_f[xi * 2 + 0 * 2 + 1];
            out_f[(xs[1] >> 4) as usize] += f_f[xi * 2 + 1 * 2 + 1];
            out_f[(xs[2] >> 4) as usize] += f_f[xi * 2 + 2 * 2 + 1];
            out_f[(xs[3] >> 4) as usize] += f_f[xi * 2 + 3 * 2 + 1];
            out_f[(xs[4] >> 4) as usize] += f_f[xi * 2 + 4 * 2 + 1];
            out_f[(xs[5] >> 4) as usize] += f_f[xi * 2 + 5 * 2 + 1];
            out_f[(xs[6] >> 4) as usize] += f_f[xi * 2 + 6 * 2 + 1];
            out_f[(xs[7] >> 4) as usize] += f_f[xi * 2 + 7 * 2 + 1];
        }
        for i in (gc * GL)..n_r_2 {
            out_f[(x_f[i] & 0x0f) as usize] += f_f[i * 2];
            out_f[(x_f[i] >> 4) as usize] += f_f[i * 2 + 1];
        }
    }
}

pub mod cimpl {
    extern "C" {
        pub fn histo(x: *const u8, v: *const f32, n_f: usize, n_r: usize, nb: usize, out: *mut f32);
        pub fn histo_8(
            x: *const u8,
            v: *const f32,
            n_f: usize,
            n_r: usize,
            nb: usize,
            out: *mut f32,
        );
    }
}
