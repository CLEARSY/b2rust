struct if_12 {
    value: i16,
}

impl if_12 {
    fn initialisation(&mut self) {
        self.value = 12;
    }

    fn might_change_value(&mut self) {
        if self.value == 10 {
            if 1 == 0 {
                self.value = (self.value).pow(
                    ((self.value).pow(((3) / (8)).try_into().unwrap()))
                        .try_into()
                        .unwrap(),
                );
            }
        }
    }
}
