fn main() {

	let mut s: main_module_01::main_module_01 = Default::default();
	let mut res: i8 = 0;
	s.sum(&1,&2,&mut res);
	assert_eq!(res,3);
	s.sum(&100,&21, &mut res);
	assert_eq!(res,4);
}
