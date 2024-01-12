fn main() {
	let mut s : main_imports_09::main_imports_09 = Default::default();
	
	
	let mut  res : i8 = 0;
	s.total(&mut res);
	assert_eq!(res,15);
	
	s.__M1_imported.write().unwrap().r#cv = 1;
	s.total(&mut res);
	assert_eq!(res,11);
	

}
