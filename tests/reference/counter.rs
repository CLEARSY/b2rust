struct counter {
    overflow: bool,
    value: i32,
}

impl counter {
    fn initialisation(&mut self) {
        self.value = 0;
        self.overflow = false;
    }

    fn zero(&mut self) {
        self.value = 0;
        self.overflow = false;
    }

    fn inc(&mut self) {
        if self.value < 2147483647 {
            self.value = (self.value) + (1);
        } else {
            self.overflow = true;
        }
    }
}
