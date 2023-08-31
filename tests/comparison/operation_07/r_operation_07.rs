use std::convert::TryFrom;

pub struct operation_07 {}

impl Default for operation_07 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl operation_07 {
    fn initialisation(&mut self) {}

    pub fn dummy_function(&mut self, r#boolean: &bool, r#value: &i8, r#other_value: &i32) {
        {
            let mut r#locale: bool = Default::default();
            r#locale = bool::try_from(false).unwrap();
        }
    }
}
