fn main() {
    let mut s: operation_06::operation_06 = Default::default();

    let mut integer: i8 = 7;
    let mut boolean: bool = true;
    let mut other_integer: i32 = 72389;
    s.return_3_false_1024(&mut integer, &mut boolean, &mut other_integer);
    assert_eq!(integer, 3);
    assert_eq!(boolean, false);
    assert_eq!(other_integer, 1024); 


    let mut integer: i8 = -67;
    let mut boolean: bool = false;
    let mut other_integer: i32 = -267278;
    s.return_3_false_1024(&mut integer, &mut boolean, &mut other_integer);
    assert_eq!(integer, 3);
    assert_eq!(boolean, false);
    assert_eq!(other_integer, 1024); 
}
