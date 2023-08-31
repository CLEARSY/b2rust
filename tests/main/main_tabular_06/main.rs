fn main() {
    let mut s: main_tabular_06::main_tabular_06 = Default::default();

    // `get_tab` is supposed to return something of type `0..5 --> rust_bool`.
    let mut the_tab: [bool; 6] = Default::default();
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [false, true, false, false, false, true]);

    the_tab = [true, false, true, true, true, false];

    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [false, true, false, false, false, true]);

    s.reset(&0);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [true, true, false, false, false, true]);

    s.reset(&2);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [true, true, true, false, false, true]);

    s.reset(&2);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [true, true, true, false, false, true]);

    s.reset(&5);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [true, true, true, false, false, true]);
}
