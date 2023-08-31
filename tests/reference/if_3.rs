struct if_3 {
    metro_i: i32,
    train_i: i32,
}

impl if_3 {
    fn initialisation(&mut self) {
        self.train_i = 12;
        self.metro_i = 62;
    }

    fn might_change_train(&mut self) {
        if self.metro_i < self.train_i {
            self.train_i = 12;
        }
    }
}
