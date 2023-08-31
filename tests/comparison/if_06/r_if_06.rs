use std::convert::TryFrom;

pub struct if_06 {
    // Concrete variables.
    pub r#value: i16,
}

impl Default for if_06 {
    fn default() -> Self {
        let mut instance = Self {
            r#value: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl if_06 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i16::try_from(12).unwrap();
    }

    pub fn might_change_value(&mut self) {
        if self.r#value < 1000 {
            if self.r#value != 0 {
                self.r#value = i16::try_from(((self.r#value) + (1))).unwrap();
            }
        } else {
            if self.r#value > 0 {
                self.r#value = i16::try_from(((self.r#value) - (1))).unwrap();
            }
        }
    }
}
