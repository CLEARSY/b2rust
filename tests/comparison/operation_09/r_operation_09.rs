use std::convert::TryFrom;

pub struct operation_09 {}

impl Default for operation_09 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl operation_09 {
    fn initialisation(&mut self) {}

    pub fn dummy_return(&mut self, r#value: &i32, r#value_r: &mut i32) {
        if ((*r#value > 1024) && (*r#value > 1024)) || ((*r#value > 1024) && (1024 < 1024)) {
            *r#value_r =
                i32::try_from((((*r#value) + ((600) * (2))) + ((6) * (*r#value)))).unwrap();
        }
        *r#value_r = i32::try_from(*r#value).unwrap();
    }
}
