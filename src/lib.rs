pub fn histo(x: &[u8], v: &[f32], n_f: usize, n_r: usize, nb: usize, out: &mut [f32]) {
    let n_r_2 = n_r / 2;
    for f in 0..n_f {
        let x_f = &x[(n_r_2 * f)..(f * n_r_2 + n_r_2)];
        let f_f = &v[(n_r * f)..(n_r * f + n_r)];
        let mut out_f = &mut out[(nb * f)..(nb * f + nb)];
        for i in 0..n_r_2 {
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
