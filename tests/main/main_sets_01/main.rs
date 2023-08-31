fn main() {
    let mut s: main_sets_01::main_sets_01 = Default::default();

    let mut the_color: main_sets_01::color = Default::default();
    s.return_red(&mut the_color);
    assert_eq!(the_color, main_sets_01::color::red);
}
