use std::convert::TryFrom;

pub struct operation_06 {}

impl Default for operation_06 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl operation_06 {
    fn initialisation(&mut self) {}

    pub fn return_3_false_1024(
        &mut self,
        r#integer: &mut i8,
        r#boolean: &mut bool,
        r#other_integer: &mut i32,
    ) {
        *r#integer = i8::try_from(3).unwrap();
        *r#boolean = bool::try_from(false).unwrap();
        *r#other_integer = i32::try_from(1024).unwrap();
    }
}
