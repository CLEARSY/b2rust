use std::convert::TryFrom;

pub struct main_while_01 {}

impl Default for main_while_01 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl main_while_01 {
    fn initialisation(&mut self) {}

    pub fn sum(&mut self, r#integer: &i16, r#result: &mut i16) {
        {
            let mut r#ii: i16 = Default::default();
            r#ii = i16::try_from(0).unwrap();
            *r#result = i16::try_from(0).unwrap();
            while r#ii <= *r#integer {
                *r#result = i16::try_from(((*r#result) + (r#ii))).unwrap();
                r#ii = i16::try_from(((r#ii) + (1))).unwrap();
            }
        }
    }
}
