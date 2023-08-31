fn main() {
    let mut s: main_tabular_01::main_tabular_01 = Default::default();

    // `get_tab` is supposed to return something of type `0..5 --> rust_i32`.
    let mut the_tab: [i32; 6] = Default::default();
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 2, 18, 25, 32, 0]);

    the_tab = [1, 18, -6, 2, 3, 1];

    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 2, 18, 25, 32, 0]);

    s.reset(&0);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 2, 18, 25, 32, 0]);

    s.reset(&1);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 1, 18, 25, 32, 0]);

    s.reset(&1);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 1, 18, 25, 32, 0]);

    s.reset(&3);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 1, 18, 1, 32, 0]);

    s.reset(&5);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 1, 18, 1, 32, 1]);
}

