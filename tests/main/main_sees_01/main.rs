


fn main(){
	let mut s : main_sees_01::main_sees_01 = Default::default();
	
	let mut res: main_sees_01::color = Default::default();
	s.op(&44,&mut res);
	assert_eq!(res, main_sees_01::color::red);
	
	let mut res2 :i8 = 0;
	s.vv_access(&1, &mut res2);
	assert_eq!(res2,11);
}
