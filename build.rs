fn main() {
    println!("cargo:rerun-if-changed=histo.h");
    println!("cargo:rerun-if-changed=histo.cc");

    let mut build = cc::Build::new();
    build
        .files(["src/histo.cc"])
        .include("src")
        .flag("-std=c++20")
        .compile("histo");
}
