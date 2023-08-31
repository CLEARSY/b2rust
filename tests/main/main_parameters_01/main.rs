fn main() {
	let mut s : main_parameters_01::main_parameters_01 = Default::default();
	
	let mut res : i8 = 0;
	s.total(&mut res);
	assert_eq!(res,30);
}
