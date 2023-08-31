fn main(){
    let mut s: main_case_02::main_case_02 = Default::default();

    let mut res: bool = true;
    s.meilleur(&2, &1, &mut res);
    assert_eq!(res, false);
    s.meilleur(&6, &2,&mut res);
    assert_eq!(res, true);
    s.meilleur(&6, &7,&mut res);
    assert_eq!(res, true);
    s.meilleur(&1, &8,&mut res);
    assert_eq!(res, true);
    s.meilleur(&5, &9,&mut res);
    assert_eq!(res, false);
}
