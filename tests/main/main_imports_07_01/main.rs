fn main() {
    let mut s: main_imports_07_01::main_imports_07_01 = Default::default();

    let mut var: i32 = 8;
    let mut result: bool = false;
    s.is_more(&var, &mut result);
    assert_eq!(result, false);

    var = -128;
    result = true;
    s.is_more(&var, &mut result);
    assert_eq!(result, false);

    var = 12048;
    result = true;
    s.is_more(&var, &mut result);
    assert_eq!(result, true);

    var = 13;
    result = false;
    s.is_more(&var, &mut result);
    assert_eq!(result, true);

    var = 12;
    result = false;
    s.is_more(&var, &mut result);
    assert_eq!(result, false);
}
