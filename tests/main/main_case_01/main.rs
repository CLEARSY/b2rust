fn main(){
    let mut s: main_case_01::main_case_01 = Default::default();
    let mut res: bool = true;
    s.meilleur(&2, &mut res);
    assert_eq!(res, false);
    s.meilleur(&6, &mut res);
    assert_eq!(res, true);
}
