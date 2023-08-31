use std::convert::TryFrom;

pub struct operation_08 {
    // Concrete variables.
    pub r#var1: i32,
    pub r#var2: i8,
}

impl Default for operation_08 {
    fn default() -> Self {
        let mut instance = Self {
            r#var1: i32::default(),
            r#var2: i8::default(),
        };
        instance.initialisation();
        instance
    }
}
impl operation_08 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#var1 = i32::try_from(0).unwrap();
        self.r#var2 = i8::try_from(0).unwrap();
    }

    pub fn dummy_return(
        &mut self,
        r#boolean: &bool,
        r#value: &i8,
        r#other_value: &i32,
        r#boolean_r: &mut bool,
        r#value_r: &mut i8,
        r#other_value_r: &mut i32,
    ) {
        self.r#var1 = i32::try_from(*r#other_value).unwrap();
        {
            let mut r#locale: i32 = Default::default();
            r#locale = i32::try_from(self.r#var1).unwrap();
            *r#other_value_r = i32::try_from(r#locale).unwrap();
        }
        *r#boolean_r = bool::try_from(*r#boolean).unwrap();
        *r#value_r = i8::try_from(*r#value).unwrap();
    }
}
