fn main() {
	let mut s : main_tabular_13::main_tabular_13 = Default::default();
	
	let mut res : i32 = 0;
	
	s.access(&2,&2,&mut res);
	assert_eq!(res,2);
}
