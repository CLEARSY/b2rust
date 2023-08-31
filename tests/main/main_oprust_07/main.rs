fn main() {
	let mut s : main_oprust_07::main_oprust_07 = Default::default();
	
	let mut res : i8 = 0;
	s.som(&1,&2,&3,&mut res);
	assert_eq!(res,6);
}
