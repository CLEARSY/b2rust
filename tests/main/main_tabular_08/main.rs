fn main() {
    let mut s: main_tabular_08::main_tabular_08 = Default::default();

    // tab : 0..2 --> (0..2 --> rust_i8)
    let mut the_tab: [[i8; 3]; 3] = Default::default();
    s.get_tab(&mut the_tab);
    // {0 |-> {0 |-> 1, 1 |-> 2, 2 |-> 3}, 1 |-> {0 |-> 1, 1 |-> 2, 2 |-> 3}, 2 |-> {0 |-> 1, 1 |-> 2, 2 |-> 3}}
    assert_eq!(the_tab, [[1, 2, 3], [1, 2, 3], [1, 2, 3]]);

    the_tab = [[8, 2, 7], [1, -7, 2], [120, 12, -38]];

    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [[1, 2, 3], [1, 2, 3], [1, 2, 3]]);

    s.reset(&0, &0);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [[0, 2, 3], [1, 2, 3], [1, 2, 3]]);

    s.reset(&0, &2);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [[0, 2, 0], [1, 2, 3], [1, 2, 3]]);

    s.reset(&2, &2);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [[0, 2, 0], [1, 2, 3], [1, 2, 0]]);

    s.reset(&2, &2);
    s.get_tab(&mut the_tab);
    assert_eq!(the_tab, [[0, 2, 0], [1, 2, 3], [1, 2, 0]]);
}

