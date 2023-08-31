fn main() {

	let mut s : main_tabular_11::main_tabular_11 = Default::default();
	let mut tab : [u8; 256] = [0;256];
	s.setValue(&3,&10,&mut tab);
	
	assert_eq!(tab[0], 0);
	assert_eq!(tab[3], 10);
}
