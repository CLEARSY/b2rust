fn main() {
    let mut s: operation_09::operation_09 = Default::default();

    let mut value: i32 = 72389;
    s.dummy_return(&-569, &mut value);
    assert_eq!(value, -569);

    value = -1723890;
    s.dummy_return(&12, &mut value);
    assert_eq!(value, 12);
}

