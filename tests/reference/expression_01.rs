struct expression_01 {
    value: i32,
}

impl expression_01 {
    fn initialisation(&mut self) {
        self.value = 0;
    }

    fn adding(&mut self) {
        if self.value == 12 {
            self.value = (self.value) * (200);
            self.value = (self.value) - (70000);
            self.value = (self.value) + (67600);
        }
    }
}
