struct if_1 {
    train_i: i32,
}

impl if_1 {
    fn initialisation(&mut self) {
        self.train_i = 12;
    }

    fn might_change_train(&mut self) {
        if 1 == 1 {
            self.train_i = -60;
        }
    }
}
