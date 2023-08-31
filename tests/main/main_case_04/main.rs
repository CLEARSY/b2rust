fn main(){
    let mut s: main_case_04::main_case_04 = Default::default();

    let mut res: bool = false;
    s.meilleur(&5, &mut res);
    assert_eq!(res, true);
    s.meilleur(&5, &mut res);
    assert_eq!(res, true);
}
