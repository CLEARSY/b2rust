use std::convert::TryFrom;

pub struct global_variable_multiple_2 {
    // Concrete variables.
    pub r#OuiGo: i8,
    pub r#trains: i16,
}

impl Default for global_variable_multiple_2 {
    fn default() -> Self {
        let mut instance = Self {
            r#OuiGo: i8::default(),
            r#trains: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl global_variable_multiple_2 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#trains = i16::try_from(56).unwrap();
        self.r#OuiGo = i8::try_from(self.r#trains).unwrap();
        self.r#trains = i16::try_from(256).unwrap();
        self.r#trains = i16::try_from(self.r#OuiGo).unwrap();
    }
}
