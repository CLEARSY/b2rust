use std::convert::TryFrom;

pub struct if_1 {
    // Concrete variables.
    pub r#train_i: i32,
}

impl Default for if_1 {
    fn default() -> Self {
        let mut instance = Self {
            r#train_i: i32::default(),
        };
        instance.initialisation();
        instance
    }
}
impl if_1 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#train_i = i32::try_from(12).unwrap();
    }

    pub fn might_change_train(&mut self) {
        if 1 == 1 {
            self.r#train_i = i32::try_from(-60).unwrap();
        }
    }
}
