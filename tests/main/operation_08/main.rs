fn main() {
    let mut s: operation_08::operation_08 = Default::default();

    let mut boolean: bool = true;
    let mut integer: i8 = 7;
    let mut other_integer: i32 = 72389;
    s.dummy_return(&true, &14, &485, &mut boolean, &mut integer, &mut other_integer);
    assert_eq!(boolean, true);
    assert_eq!(integer, 14);
    assert_eq!(other_integer, 485); 


    let mut boolean: bool = false;
    let mut integer: i8 = -58;
    let mut other_integer: i32 = 0;
    s.dummy_return(&true, &0, &-457, &mut boolean, &mut integer, &mut other_integer);
    assert_eq!(boolean, true);
    assert_eq!(integer, 0);
    assert_eq!(other_integer, -457); 
}
