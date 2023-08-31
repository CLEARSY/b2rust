use std::convert::TryFrom;

pub struct concrete_constant_01 {}

impl Default for concrete_constant_01 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl concrete_constant_01 {
    // Constant’s `VALUES`.
    pub const r#size_v: i8 = 7;
    pub const r#employees: i8 = 13;
    pub const r#is_the_machine_on: bool = true;
    pub const r#annual_growth: i32 = -3615;
    fn initialisation(&mut self) {}
}
