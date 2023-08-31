struct concrete_constant_01 {
    annual_growth: i32,
    employees: i8,
    is_the_machine_on: bool,
    size_v: i8,
}

impl concrete_constant_01 {
    fn initialisation(&mut self) {
        self.annual_growth = -3615;
        self.employees = 13;
        self.is_the_machine_on = true;
        self.size_v = 7;
    }
}
