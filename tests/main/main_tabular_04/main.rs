fn main() {
    let mut s: main_tabular_04::main_tabular_04 = Default::default();

    // `get_tab` is supposed to return something of type `0..5 --> rust_i32`.


    // {0 |-> 1, 1 |-> 2, 2 |-> 18, 3 |-> 25, 4 |-> 32, 5 |-> 0}

    let mut res: i32 = 0;
    s.get_element(&0, &mut res);
    assert_eq!(res, 1);

    s.get_element(&0, &mut res);
    assert_eq!(res, 1);

    s.get_element(&1, &mut res);
    assert_eq!(res, 2);

    s.get_element(&5, &mut res);
    assert_eq!(res, 0);
}
