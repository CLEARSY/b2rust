fn main() {

	let mut s : main_oprust_06::main_oprust_06 = Default::default();
	
	let tab1 : [u8;256] = [1;256];
	let mut res : main_oprust_06::ANIMAL = Default::default();
	
	s.compliquee(&1,&1,&1,&tab1,&mut res);
	assert_eq!(res,  main_oprust_06::ANIMAL::CAT);
}
