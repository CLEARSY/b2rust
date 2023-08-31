struct global_variable_multiple_2 {
    OuiGo: i8,
    trains: i16,
}

impl global_variable_multiple_2 {
    fn initialisation(&mut self) {
        self.trains = 56;
        self.OuiGo = self.trains;
        self.trains = 256;
        self.trains = self.OuiGo;
    }
}
