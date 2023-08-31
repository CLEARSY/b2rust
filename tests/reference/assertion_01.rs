struct assertion_01 {
    var1: i32,
    var2: i32,
    var3: i32,
}

impl assertion_01 {
    fn initialisation(&mut self) {
        self.var1 = 0;
        self.var2 = 10;
        self.var3 = 3615;
    }

    fn dummy_inversion(&mut self) {
        self.var3 = self.var1;
        self.var1 = self.var2;
        self.var2 = self.var3;
        self.var2 = self.var3;
    }
}
