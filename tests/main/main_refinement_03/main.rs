fn main(){
    let mut s: main_refinement_03::main_refinement_03 = Default::default();
    
    let mut res : i8 = 0;
    s.sum(&mut res);
    assert_eq!(res,14);
    
}
    
