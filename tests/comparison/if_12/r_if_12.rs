use std::convert::TryFrom;

pub struct if_12 {
    // Concrete variables.
    pub r#value: i16,
}

impl Default for if_12 {
    fn default() -> Self {
        let mut instance = Self {
            r#value: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl if_12 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i16::try_from(12).unwrap();
    }

    pub fn might_change_value(&mut self) {
        if self.r#value == 10 {
            if 1 == 0 {
                self.r#value = i16::try_from(
                    (self.r#value).pow(((self.r#value).pow(((3) / (8)) as u32)) as u32),
                )
                .unwrap();
            }
        }
    }
}
