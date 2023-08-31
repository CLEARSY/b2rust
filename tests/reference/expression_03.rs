struct expression_03 {
    value: i32,
}

impl expression_03 {
    fn initialisation(&mut self) {
        self.value = 0;
    }

    fn modify(&mut self) {
        self.value = (self.value) % (10);
    }

    fn modify_again(&mut self) {
        self.value = ((self.value) + (67)) % (((self.value) * (2)) / (2));
    }
}
