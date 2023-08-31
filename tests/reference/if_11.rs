struct if_11 {
    value: i16,
}

impl if_11 {
    fn initialisation(&mut self) {
        self.value = 12;
    }

    fn might_change_value(&mut self) {
        if (self.value) / (2) == 6 {
            self.value = (self.value) / (2);
        }
    }
}
