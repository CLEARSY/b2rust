struct expression_02 {
    value: i32,
}

impl expression_02 {
    fn initialisation(&mut self) {
        self.value = 0;
    }

    fn modify(&mut self) {
        if (self.value > 2) && (self.value < 4) {
            self.value = ((self.value) + (7)).pow(((self.value) - (2)).try_into().unwrap());
        }
    }
}
