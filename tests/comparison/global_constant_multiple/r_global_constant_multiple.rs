use std::convert::TryFrom;

pub struct global_constant_multiple {}

impl Default for global_constant_multiple {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl global_constant_multiple {
    // Constant’s `VALUES`.
    pub const r#size_v: i8 = 7;
    pub const r#is_the_machine_on: bool = true;
    pub const r#annual_growth: i32 = -3615;
    fn initialisation(&mut self) {}
}
