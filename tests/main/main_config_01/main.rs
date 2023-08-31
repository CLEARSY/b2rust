fn main(){
    let mut s: main_config_01::main_config_01 = Default::default();
    
    let mut res:i8 = 0;
    s.sum(&mut res);
    assert_eq!(res,9);
    
}
    
