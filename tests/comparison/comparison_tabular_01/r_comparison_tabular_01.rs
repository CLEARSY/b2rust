use std::convert::TryFrom;

pub struct comparison_tabular_01 {
    // Concrete variables.
    pub r#tab2: [bool; (1 + 1) as usize],
}

impl Default for comparison_tabular_01 {
    fn default() -> Self {
        let mut instance = Self {
            r#tab2: [bool::default(); (1 + 1) as usize],
        };
        instance.initialisation();
        instance
    }
}
impl comparison_tabular_01 {
    // Constant’s `VALUES`.
    pub const r#tab: [i32; (5 + 1) as usize] = [1, 2, 18, 25, 32, 0];
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#tab2 = [true, false];
    }
}
