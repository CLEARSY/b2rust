struct if_09 {
    value: i16,
}

impl if_09 {
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
            if (((self.value == 0) || (self.value >= 500)) || (self.value == 0))
                && (self.value >= 0)
            {
                if self.value == 0 {
                    self.value = (self.value) + (1);
                }
            }
        }
    }
}
