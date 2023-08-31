fn main(){
	let mut s : main_imports_08::main_imports_08 = Default::default();
	
	let mut res : i8 = 0;
	s.op(&mut res);
	assert_eq!(res,32);
}
