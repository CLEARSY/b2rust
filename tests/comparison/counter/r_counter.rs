use std::convert::TryFrom;

pub struct counter {
    // Concrete variables.
    pub r#overflow: bool,
    pub r#value: i32,
}

impl Default for counter {
    fn default() -> Self {
        let mut instance = Self {
            r#overflow: bool::default(),
            r#value: i32::default(),
        };
        instance.initialisation();
        instance
    }
}
impl counter {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i32::try_from(0).unwrap();
        self.r#overflow = bool::try_from(false).unwrap();
    }

    pub fn zero(&mut self) {
        self.r#value = i32::try_from(0).unwrap();
        self.r#overflow = bool::try_from(false).unwrap();
    }

    pub fn inc(&mut self) {
        if self.r#value < 2147483647 {
            self.r#value = i32::try_from(((self.r#value) + (1))).unwrap();
        } else {
            self.r#overflow = bool::try_from(true).unwrap();
        }
    }
}
