fn main() {
	let mut s : main_promotes_01::main_promotes_01 = Default::default();
	
	let mut toto :i8 = 0;
	s.op_01(&mut toto);
	assert_eq!(toto,2);
	s.op_01_01(&mut toto);
	assert_eq!(toto,1);



}
