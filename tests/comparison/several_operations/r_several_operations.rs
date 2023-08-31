use std::convert::TryFrom;

pub struct several_operations {}

impl Default for several_operations {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl several_operations {
    fn initialisation(&mut self) {}

    pub fn do_nothing(&mut self) {}

    pub fn do_nothing_bis(&mut self) {}

    pub fn do_nothing_too(&mut self) {}
}
