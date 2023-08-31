fn main() {
    let mut s: main_assertion_01::main_assertion_01 = Default::default();

    let mut var: i32 = 8;
    s.inc(&62, &mut var);
    assert_eq!(var, 63);

    s.inc(&-45678, &mut var);
    assert_eq!(var, -45677);

    s.inc(&0, &mut var);
    assert_eq!(var, 1);

    var = 256;
    s.inc(&-69065, &mut var);
    assert_eq!(var, -69064);

    s.inc(&-2147483648, &mut var);
    assert_eq!(var, -2147483647);

    s.inc(&2147483647, &mut var);
    assert_eq!(var, 0);

    s.inc(&1000, &mut var);
    assert_eq!(var, 1001);

    s.inc(&1001, &mut var);
    assert_eq!(var, 0);
}
