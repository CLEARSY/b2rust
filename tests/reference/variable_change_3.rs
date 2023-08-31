struct variable_change_3 {
    hour: i8,
    hour_default: i8,
    roads_i: i32,
    traffic_state_i: bool,
    trains_i: i16,
}

impl variable_change_3 {
    fn initialisation(&mut self) {
        self.hour = 14;
        self.trains_i = 56;
        self.traffic_state_i = true;
        self.roads_i = 26239;
        self.traffic_state_i = false;
        self.hour_default = 5;
    }

    fn reset_hour(&mut self) {
        self.hour = self.hour_default;
    }
}
