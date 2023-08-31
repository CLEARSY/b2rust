use std::convert::TryFrom;

pub struct local_variable_03 {}

impl Default for local_variable_03 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl local_variable_03 {
    fn initialisation(&mut self) {}

    pub fn dummy_function(&mut self) {
        {
            let mut r#locale2: i32 = Default::default();
            r#locale2 = i32::try_from(1234).unwrap();
            r#locale2 = i32::try_from(63).unwrap();
        }
    }
}
