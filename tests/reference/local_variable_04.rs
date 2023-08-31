struct local_variable_04 {
    var: i32,
    var2: bool,
}

impl local_variable_04 {
    fn initialisation(&mut self) {
        self.var = 7348;
        self.var2 = true;
    }

    fn dummy_function(&mut self) {
        {
            let mut locale2: i32;
            let mut locale8: bool;
            locale2 = 9;
            locale8 = false;
            self.var = ((locale2) * (2)) + (locale2);
            self.var2 = true;
            self.var2 = locale8;
        }
    }
}
