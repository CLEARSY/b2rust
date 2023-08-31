struct expression_04 {
    value: i32,
}

impl expression_04 {
    fn initialisation(&mut self) {
        self.value = 0;
    }

    fn modify(&mut self) {
        self.value = (self.value) * ((2) + (2));
    }
}
