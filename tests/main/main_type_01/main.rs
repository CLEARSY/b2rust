

fn main() {
	let mut s : main_type_01::main_type_01 = Default::default();
	let cc1 : u8 = 10;
	assert_eq!(main_type_01::main_type_01::r#cc1,cc1);
	let cc2: i8 =15;
	assert_eq!(main_type_01::main_type_01::r#cc2,cc2);	
	let cv1: u32 =0;
	assert_eq!(s.r#cv1,cv1);
	let cv2: u8= 1;
	assert_eq!(s.r#cv2,cv2);
}

