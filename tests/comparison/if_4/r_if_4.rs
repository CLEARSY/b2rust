use std::convert::TryFrom;

pub struct if_4 {
    // Concrete variables.
    pub r#metro_i: i32,
    pub r#train_i: i32,
}

impl Default for if_4 {
    fn default() -> Self {
        let mut instance = Self {
            r#metro_i: i32::default(),
            r#train_i: i32::default(),
        };
        instance.initialisation();
        instance
    }
}
impl if_4 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#train_i = i32::try_from(12).unwrap();
        self.r#metro_i = i32::try_from(62).unwrap();
    }

    pub fn might_change_train(&mut self) {
        if self.r#metro_i < self.r#train_i {
            self.r#train_i = i32::try_from(12).unwrap();
        } else {
            self.r#metro_i = i32::try_from(62).unwrap();
        }
    }
}
