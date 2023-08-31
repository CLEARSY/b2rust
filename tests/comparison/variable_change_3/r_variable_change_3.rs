use std::convert::TryFrom;

pub struct variable_change_3 {
    // Concrete variables.
    pub r#hour: i8,
    pub r#hour_default: i8,
    pub r#roads_i: i32,
    pub r#traffic_state_i: bool,
    pub r#trains_i: i16,
}

impl Default for variable_change_3 {
    fn default() -> Self {
        let mut instance = Self {
            r#hour: i8::default(),
            r#hour_default: i8::default(),
            r#roads_i: i32::default(),
            r#traffic_state_i: bool::default(),
            r#trains_i: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl variable_change_3 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#hour = i8::try_from(14).unwrap();
        self.r#trains_i = i16::try_from(56).unwrap();
        self.r#traffic_state_i = bool::try_from(true).unwrap();
        self.r#roads_i = i32::try_from(26239).unwrap();
        self.r#traffic_state_i = bool::try_from(false).unwrap();
        self.r#hour_default = i8::try_from(5).unwrap();
    }

    pub fn reset_hour(&mut self) {
        self.r#hour = i8::try_from(self.r#hour_default).unwrap();
    }
}
