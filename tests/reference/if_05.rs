struct if_05 {
    value: i16,
}

impl if_05 {
    fn initialisation(&mut self) {
        self.value = 12;
    }

    fn might_change_value(&mut self) {
        if self.value < 1000 {
            self.value = (self.value) + (1);
        } else {
            if self.value > 0 {
                self.value = (self.value) - (1);
            }
        }
    }
}
