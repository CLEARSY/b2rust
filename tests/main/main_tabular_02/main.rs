fn main() {
    let mut s: main_tabular_02::main_tabular_02 = Default::default();

    // `get_tab` is supposed to return something of type `0..5 --> rust_i32`.
    let mut the_tab: [i32; 6] = Default::default();
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 2, 18, 25, 32, 0]);

    the_tab = [1, 18, -6, 2, 3, 1];

    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [1, 2, 18, 25, 32, 0]);

    s.change();
    the_tab = Default::default();
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [7, -2, -18, -25, 3, 1]);
}
