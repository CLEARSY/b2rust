use std::convert::TryFrom;

pub struct if_11 {
    // Concrete variables.
    pub r#value: i16,
}

impl Default for if_11 {
    fn default() -> Self {
        let mut instance = Self {
            r#value: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl if_11 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i16::try_from(12).unwrap();
    }

    pub fn might_change_value(&mut self) {
        if ((self.r#value) / (2)) == 6 {
            self.r#value = i16::try_from(((self.r#value) / (2))).unwrap();
        }
    }
}
