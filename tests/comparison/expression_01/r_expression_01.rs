use std::convert::TryFrom;

pub struct expression_01 {
    // Concrete variables.
    pub r#value: i32,
}

impl Default for expression_01 {
    fn default() -> Self {
        let mut instance = Self {
            r#value: i32::default(),
        };
        instance.initialisation();
        instance
    }
}
impl expression_01 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i32::try_from(0).unwrap();
    }

    pub fn adding(&mut self) {
        if self.r#value == 12 {
            self.r#value = i32::try_from(((self.r#value) * (200))).unwrap();
            self.r#value = i32::try_from(((self.r#value) - (70000))).unwrap();
            self.r#value = i32::try_from(((self.r#value) + (67600))).unwrap();
        }
    }
}
