struct becomes_in {
    var1: i32,
}

impl becomes_in {
    fn initialisation(&mut self) {
        self.var1 = 5;
    }

    fn dummy_function(&mut self) {
        {
            let locale2: i32;
            locale2 = 1234;
            locale2 = 674;
            self.var1 = locale2;
        }
    }
}
