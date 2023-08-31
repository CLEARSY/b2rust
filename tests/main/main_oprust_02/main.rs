fn main(){
    let mut s: main_oprust_02::main_oprust_02 = Default::default();
    
    let mut res : i8 = 0;
    s.compliquer(&1,&2,&mut res);
    assert_eq!(res,0);
}
