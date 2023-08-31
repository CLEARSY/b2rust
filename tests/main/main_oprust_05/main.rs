fn main() {
    let mut s: main_oprust_05::main_oprust_05 = Default::default();

    let mut res: i8 = 0;
    s.complique(&10, &2, &mut res);
    assert_eq!(res, 1);

    s.complique(&10, &8, &mut res);
    assert_eq!(res, 100);
}
