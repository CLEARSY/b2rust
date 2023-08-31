use std::convert::TryFrom;

pub struct operation_01 {}

impl Default for operation_01 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl operation_01 {
    fn initialisation(&mut self) {}

    pub fn return_true(&mut self, r#boolean: &mut bool) {
        *r#boolean = bool::try_from(true).unwrap();
    }
}
