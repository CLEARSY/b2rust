fn main() {
    let mut s: main_string_01::main_string_01 = Default::default();

    let mut res: i8 = 0;
    s.noOverflow(&1, &2, &mut res);
    assert_eq!(res, 3);

    s.noOverflow(&120, &10, &mut res);
    assert_eq!(res, 3);
}
