fn main() {
	let mut s : main_promotes_04::main_promotes_04 = Default::default();
	
	let mut res :i8 = 12;
	s.op(&mut res);
	assert_eq!(res,0);
	
	s.op_01(&mut res);
	assert_eq!(res,1);
	
	s.op_02(&mut res);
	assert_eq!(res,2);
	
	s.op_03a(&10,&mut res);
	assert_eq!(res,10);

	s.op_03b(&mut res);
	assert_eq!(res,8);

}
