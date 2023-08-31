use std::convert::TryFrom;

pub struct expression_02 {
    // Concrete variables.
    pub r#value: i32,
}

impl Default for expression_02 {
    fn default() -> Self {
        let mut instance = Self {
            r#value: i32::default(),
        };
        instance.initialisation();
        instance
    }
}
impl expression_02 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#value = i32::try_from(0).unwrap();
    }

    pub fn modify(&mut self) {
        if (self.r#value > 2) && (self.r#value < 4) {
            self.r#value =
                i32::try_from(((self.r#value) + (7)).pow(((self.r#value) - (2)) as u32)).unwrap();
        }
    }
}
