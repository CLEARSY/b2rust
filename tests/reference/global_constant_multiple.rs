struct global_constant_multiple {
    annual_growth: i32,
    is_the_machine_on: bool,
    size_v: i8,
}

impl global_constant_multiple {
    fn initialisation(&mut self) {
        self.annual_growth = -3615;
        self.is_the_machine_on = true;
        self.size_v = 7;
    }
}
