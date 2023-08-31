fn main() {
    let mut s: operation_01::operation_01 = Default::default();

    let mut boolean: bool = true;
    s.return_true(&mut boolean);
    assert_eq!(boolean, true);

    boolean = false;
    s.return_true(&mut boolean);
    assert_eq!(boolean, true);
}
