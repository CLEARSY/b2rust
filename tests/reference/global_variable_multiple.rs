struct global_variable_multiple {
    roads_i: i32,
    traffic_state_i: bool,
    trains_i: i16,
}

impl global_variable_multiple {
    fn initialisation(&mut self) {
        self.trains_i = 56;
        self.traffic_state_i = true;
        self.roads_i = 26239;
        self.traffic_state_i = false;
    }
}
