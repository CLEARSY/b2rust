fn main() {
    let mut s: main_imports_03_01::main_imports_03_01 = Default::default();

    let mut var: i16 = 8;
    s.get_var(&mut var);
    assert_eq!(var, 0);

    s.inc();

    s.get_var(&mut var);
    assert_eq!(var, 1);

    s.inc();
    s.inc();

    s.get_var(&mut var);
    assert_eq!(var, 3);

    for n in 3..999 {
	s.inc();
    }

    s.get_var(&mut var);
    assert_eq!(var, 999);

    s.inc();

    s.get_var(&mut var);
    assert_eq!(var, 1000);

    s.inc();

    s.get_var(&mut var);
    assert_eq!(var, 1000);

    s.inc();

    s.get_var(&mut var);
    assert_eq!(var, 1000);
}
