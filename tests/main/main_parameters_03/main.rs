fn main() {
	let mut s : main_parameters_03::main_parameters_03 = main_parameters_03::main_parameters_03::new(5);
	
	let mut res : i8 = 0;
	s.total(&mut res);
	assert_eq!(res,115);


}
