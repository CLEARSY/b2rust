use std::convert::TryFrom;

pub struct assertion_02 {
    // Concrete variables.
    pub r#var1: i32,
    pub r#var2: i32,
    pub r#var3: i32,
}

impl Default for assertion_02 {
    fn default() -> Self {
        let mut instance = Self {
            r#var1: i32::default(),
            r#var2: i32::default(),
            r#var3: i32::default(),
        };
        instance.initialisation();
        instance
    }
}
impl assertion_02 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#var1 = i32::try_from(0).unwrap();
        self.r#var2 = i32::try_from(10).unwrap();
        self.r#var3 = i32::try_from(3615).unwrap();
    }

    pub fn zero(&mut self) {
        self.r#var1 = i32::try_from(0).unwrap();
        self.r#var2 = i32::try_from(0).unwrap();
        self.r#var3 = i32::try_from(0).unwrap();
        self.r#var1 = i32::try_from(0).unwrap();
    }
}
