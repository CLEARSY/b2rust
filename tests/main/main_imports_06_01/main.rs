fn main() {
    let mut s: main_imports_06_01::main_imports_06_01 = Default::default();
    let mut v_true: bool = false;
    let mut v_false: bool = false;
    s.set_true_false_to(&true, &false);
    s.return_var_true(&mut v_true);
    s.return_var_false(&mut v_false);

    assert_eq!(v_true, true);
    assert_eq!(v_false, false);


    s.set_true_false_to(&false, &true);
    s.return_var_true(&mut v_true);
    s.return_var_false(&mut v_false);

    assert_eq!(v_true, false);
    assert_eq!(v_false, true);

    s.reset();
    s.return_var_true(&mut v_true);
    s.return_var_false(&mut v_false);

    assert_eq!(v_true, true);
    assert_eq!(v_false, false);

    s.reset();
    s.return_var_true(&mut v_true);
    s.return_var_false(&mut v_false);

    assert_eq!(v_true, true);
    assert_eq!(v_false, false);
}
