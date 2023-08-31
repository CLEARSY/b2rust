fn main() {
    let mut s: main_imports_02::main_imports_02 = Default::default();

    let mut int: i8 = 0;
    s.return_four(&mut int);
    assert_eq!(int, 4);

    int = 63;
    s.return_four(&mut int);
    assert_eq!(int, 4);
}
