use std::convert::TryFrom;

pub struct if_09 {
    // Concrete variables.
    pub r#value: i16,
}

impl Default for if_09 {
    fn default() -> Self {
        let mut instance = Self {
            r#value: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl if_09 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i16::try_from(12).unwrap();
    }

    pub fn might_change_value(&mut self) {
        if ((self.r#value > 0) && (self.r#value < 500))
            || (self.r#value == 60)
            || ((self.r#value == 2) && (self.r#value == 3))
        {
            self.r#value = i16::try_from(((self.r#value) * (2))).unwrap();
        } else {
            if (((self.r#value == 0) || (self.r#value >= 500)) || (self.r#value == 0))
                && (self.r#value >= 0)
            {
                if self.r#value == 0 {
                    self.r#value = i16::try_from(((self.r#value) + (1))).unwrap();
                }
            }
        }
    }
}
