fn main() {
    let mut s: main_imports_01::main_imports_01 = Default::default();

    let mut value: bool = false;
    s.return_true(&mut value);
    assert_eq!(value, true);
}
