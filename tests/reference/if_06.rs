struct if_06 {
    value: i16,
}

impl if_06 {
    fn initialisation(&mut self) {
        self.value = 12;
    }

    fn might_change_value(&mut self) {
        if self.value < 1000 {
            if self.value != 0 {
                self.value = (self.value) + (1);
            }
        } else {
            if self.value > 0 {
                self.value = (self.value) - (1);
            }
        }
    }
}
