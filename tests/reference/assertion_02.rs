struct assertion_02 {
    var1: i32,
    var2: i32,
    var3: i32,
}

impl assertion_02 {
    fn initialisation(&mut self) {
        self.var1 = 0;
        self.var2 = 10;
        self.var3 = 3615;
    }

    fn zero(&mut self) {
        self.var1 = 0;
        self.var2 = 0;
        self.var3 = 0;
        self.var1 = 0;
    }
}
