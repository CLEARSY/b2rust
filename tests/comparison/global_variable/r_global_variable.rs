use std::convert::TryFrom;

pub struct global_variable {
    // Concrete variables.
    pub r#number: i8,
}

impl Default for global_variable {
    fn default() -> Self {
        let mut instance = Self {
            r#number: i8::default(),
        };
        instance.initialisation();
        instance
    }
}
impl global_variable {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#number = i8::try_from(1).unwrap();
    }
}
