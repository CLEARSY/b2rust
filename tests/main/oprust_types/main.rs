fn main() {
    let mut s: oprust_types::oprust_types = Default::default();

    let mut res1: u8 = 0;
    s.lshift(&13, &3, &mut res1);
    assert_eq!(res1, 104);
}
