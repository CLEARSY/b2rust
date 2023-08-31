fn main() {
	let mut s : main_promotes_05::main_promotes_05 = Default::default();
	
	let mut res :i8 = 12;
	s.op(&mut res);
	assert_eq!(res,0);
	
	s.op_01(&mut res);
	assert_eq!(res,1);
	
	s.op_02(&mut res);
	assert_eq!(res,2);
	

}
