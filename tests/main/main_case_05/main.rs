fn main(){
    let mut s: main_case_05::main_case_05 = Default::default();

    let mut res: bool = false;
    s.meilleur(&1, &mut res);
    assert_eq!(res, false);

    s.meilleur(&3, &mut res);
    assert_eq!(res, false);

    s.meilleur(&4, &mut res);
    assert_eq!(res, false);

    s.meilleur(&5, &mut res);
    assert_eq!(res, true);

    s.meilleur(&6, &mut res);
    assert_eq!(res, true);

    s.meilleur(&7, &mut res);
    assert_eq!(res, true);

    s.meilleur(&11, &mut res);
    assert_eq!(res, true);

    s.meilleur(&-56, &mut res);
    assert_eq!(res, true);

    s.meilleur(&77, &mut res);
    assert_eq!(res, true);
}
