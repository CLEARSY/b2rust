fn main() {
    let mut s: main_operations_01_01::main_operations_01_01 = Default::default();

    let mut var: i8 = 43;
    s.return_two(&mut var);
    assert_eq!(var, 2);

    let mut entry: bool = false;
    let mut result: bool = false;
    s.return_opposite(&entry, &mut result);
    assert_eq!(result, true);

    entry = result;
    s.return_opposite(&entry, &mut result);
    assert_eq!(result, false);

    entry = result;
    s.return_opposite(&entry, &mut result);
    assert_eq!(result, true);

    s.return_two(&mut var);
    assert_eq!(var, 2);

    var = -6;
    s.return_two(&mut var);
    assert_eq!(var, 2);
}
