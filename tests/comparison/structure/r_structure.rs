use std::convert::TryFrom;

pub struct structure {}

impl Default for structure {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl structure {
    fn initialisation(&mut self) {}
}
