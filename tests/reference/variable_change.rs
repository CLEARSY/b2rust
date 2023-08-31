struct variable_change {
    hour: i8,
    roads_i: i32,
    traffic_state_i: bool,
    trains_i: i16,
}

impl variable_change {
    fn initialisation(&mut self) {
        self.hour = 14;
        self.trains_i = 56;
        self.traffic_state_i = true;
        self.roads_i = 26239;
        self.traffic_state_i = false;
    }

    fn change_me(&mut self) {
        self.hour = 19;
    }
}
