use std::convert::TryFrom;

pub struct local_variable_02 {}

impl Default for local_variable_02 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl local_variable_02 {
    fn initialisation(&mut self) {}

    pub fn dummy_function(&mut self) {
        {
            let mut r#locale: bool = Default::default();
            r#locale = bool::try_from(true).unwrap();
            r#locale = bool::try_from(false).unwrap();
            {
                let mut r#locale2: bool = Default::default();
                r#locale2 = bool::try_from(r#locale).unwrap();
                {
                    let mut r#locale6: i8 = Default::default();
                    let mut r#locale5: i32 = Default::default();
                    let mut r#locale4: bool = Default::default();
                    r#locale4 = bool::try_from(r#locale2).unwrap();
                }
                r#locale = bool::try_from(r#locale2).unwrap();
            }
            r#locale = bool::try_from(true).unwrap();
        }
    }
}
