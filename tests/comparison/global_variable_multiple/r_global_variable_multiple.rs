use std::convert::TryFrom;

pub struct global_variable_multiple {
    // Concrete variables.
    pub r#roads_i: i32,
    pub r#traffic_state_i: bool,
    pub r#trains_i: i16,
}

impl Default for global_variable_multiple {
    fn default() -> Self {
        let mut instance = Self {
            r#roads_i: i32::default(),
            r#traffic_state_i: bool::default(),
            r#trains_i: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl global_variable_multiple {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#trains_i = i16::try_from(56).unwrap();
        self.r#traffic_state_i = bool::try_from(true).unwrap();
        self.r#roads_i = i32::try_from(26239).unwrap();
        self.r#traffic_state_i = bool::try_from(false).unwrap();
    }
}
