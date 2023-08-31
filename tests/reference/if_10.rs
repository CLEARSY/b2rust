struct if_10 {
    value: i16,
}

impl if_10 {
    fn initialisation(&mut self) {
        self.value = 12;
    }

    fn might_change_value(&mut self) {
        if ((self.value > 0) && (self.value < 500))
            || (self.value == 60)
            || ((self.value == 2) && (self.value == 3))
        {
            self.value = (self.value) * (2);
        } else {
            if !(((self.value > 0) && (self.value < 500))
                || (self.value == 60)
                || ((self.value == 2) && (self.value == 3)))
            {
                if self.value == 0 {
                    self.value = (self.value) + (1);
                }
            }
        }
    }
}
