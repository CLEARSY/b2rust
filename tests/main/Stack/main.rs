fn main() {


       let mut s: Stack::Stack = Default::default();

        s.push(&5);
        s.push(&10);

        let mut value: i8 = 0;
        s.pop(&mut value);
        assert_eq!(value, 10);

        s.pop(&mut value);
        assert_eq!(value, 5);
        
}
