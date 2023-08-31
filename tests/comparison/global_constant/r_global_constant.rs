use std::convert::TryFrom;

pub struct global_constant {}

impl Default for global_constant {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl global_constant {
    // Constant’s `VALUES`.
    pub const r#growth: i32 = -2;
    fn initialisation(&mut self) {}
}
