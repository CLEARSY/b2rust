fn main() {
    let mut s: main_while_01::main_while_01 = Default::default();

    let mut result: i16 = 0;
    s.sum(&10, &mut result);
    assert_eq!(result, 55);

    result = -250;
    s.sum(&1, &mut result);
    assert_eq!(result, 1);

    result = 1;
    s.sum(&1, &mut result);
    assert_eq!(result, 1);

    result = 1;
    s.sum(&112, &mut result);
    assert_eq!(result, 6328);
}

