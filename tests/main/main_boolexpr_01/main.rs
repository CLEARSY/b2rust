fn main() {
	let mut s : main_boolexpr_01::main_boolexpr_01 = Default::default();
	
	let mut res : bool = Default::default();
	
	s.is_happy(&mut res);
	
	assert_eq!(res, true);

}
