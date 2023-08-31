fn main() {
  let mut s: main_tabular_10::main_tabular_10 = Default::default();
  
  let mut tab1 : [i32;6] = Default::default();
  let mut tab2 : [i32;6] = Default::default();
  s.get_tab1(&mut tab1);
  s.get_tab2(&mut tab2);
  
  assert_eq!(tab1,tab2);
  
  s.set_tab(&10, &mut tab1);
  assert_eq!(tab1, [10,10,10,10,10,10]);
}
