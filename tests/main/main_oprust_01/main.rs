fn main(){
    let mut s: main_oprust_01::main_oprust_01 = Default::default();
    
    let mut res : i8 = 0;
    s.add2(&1,&2,&mut res);
    assert_eq!(res,4);
}
