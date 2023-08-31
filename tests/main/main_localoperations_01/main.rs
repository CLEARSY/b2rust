fn main() {
	let mut s : main_localoperations_01::main_localoperations_01 = Default::default();
	
	s.inc10();
	assert_eq!(s.cv, 10);
	
	let mut res : i8 = 1 ;
	s.addWithCv(&10, &mut res);
	assert_eq!(res, 21);
	
	s.addWithCv(&10, &mut res);
	assert_eq!(res, 41);
	
	s.inc10();
	s.addWithCv(&0, &mut res);
	assert_eq!(res, 61);


}
