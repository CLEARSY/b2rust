use std::convert::TryFrom;

pub struct expression_04 {
    // Concrete variables.
    pub r#value: i32,
}

impl Default for expression_04 {
    fn default() -> Self {
        let mut instance = Self {
            r#value: i32::default(),
        };
        instance.initialisation();
        instance
    }
}
impl expression_04 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i32::try_from(0).unwrap();
    }

    pub fn modify(&mut self) {
        self.r#value = i32::try_from(((self.r#value) * ((2) + (2)))).unwrap();
    }
}
