fn main() {
	let mut s :main_swap_01::main_swap_01 = Default::default();
	
	assert_eq!(s.r#cv1, 10);
	assert_eq!(s.r#cv2, 20);
	assert_eq!(s.r#cv3, 30);
	assert_eq!(s.r#cv4, 40);
	
	s.bigSwap();
	assert_eq!(s.r#cv1, 20);
	assert_eq!(s.r#cv2, 30);
	assert_eq!(s.r#cv3, 40);
	assert_eq!(s.r#cv4, 10);
	

}
