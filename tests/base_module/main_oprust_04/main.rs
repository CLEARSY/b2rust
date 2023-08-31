fn main() {
    let mut s: main_oprust_04::main_oprust_04 = Default::default();
    
    let mut res : i8 = 0;
    s.and(&10,&12,&mut res);
    assert_eq!(res, 8);

    s.orr(&10,&12,&mut res);
    assert_eq!(res, 14);
    
    s.xor(&10,&12,&mut res);
    assert_eq!(res, 6);
    
    let mut res1 : u8 = 0;
    s.lshift(&13,&3,&mut res1);
    assert_eq!(res1, 104);
    
    s.rshift(&-10,&2,&mut res);
    assert_eq!(res, -3);    

}
