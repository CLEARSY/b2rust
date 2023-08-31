fn main() {
    let mut s: main_unsigned_02::main_unsigned_02 = Default::default();

    let mut var:u32 = 8;
    s.inc(&62, &mut var);
    assert_eq!(var, 63);

    s.inc(&45678, &mut var);
    assert_eq!(var, 0);

    s.inc(&0, &mut var);
    assert_eq!(var, 1);

   
}
