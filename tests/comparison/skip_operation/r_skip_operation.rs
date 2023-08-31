use std::convert::TryFrom;

pub struct skip_operation {}

impl Default for skip_operation {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl skip_operation {
    fn initialisation(&mut self) {}

    pub fn skip_me(&mut self) {}
}
