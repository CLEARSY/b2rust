use std::convert::TryFrom;

pub struct local_variable_04 {
    // Concrete variables.
    pub r#var: i32,
    pub r#var2: bool,
}

impl Default for local_variable_04 {
    fn default() -> Self {
        let mut instance = Self {
            r#var: i32::default(),
            r#var2: bool::default(),
        };
        instance.initialisation();
        instance
    }
}
impl local_variable_04 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#var = i32::try_from(7348).unwrap();
        self.r#var2 = bool::try_from(true).unwrap();
    }

    pub fn dummy_function(&mut self) {
        {
            let mut r#locale2: i32 = Default::default();
            let mut r#locale8: bool = Default::default();
            r#locale2 = i32::try_from(9).unwrap();
            r#locale8 = bool::try_from(false).unwrap();
            self.r#var = i32::try_from((((r#locale2) * (2)) + (r#locale2))).unwrap();
            self.r#var2 = bool::try_from(true).unwrap();
            self.r#var2 = bool::try_from(r#locale8).unwrap();
        }
    }
}
