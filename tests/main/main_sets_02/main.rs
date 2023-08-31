fn main() {
    let mut s: main_sets_02::main_sets_02 = Default::default();

    let mut the_color: main_sets_02::color = Default::default();
    s.something_a_human_can_see(&mut the_color);
    assert_eq!(the_color, main_sets_02::color::red);
}
