use std::convert::TryFrom;

pub struct comparison_tabular_03 {
    // Concrete variables.
    pub r#tab: [i32; (-1000 + 1) as usize],
}

impl Default for comparison_tabular_03 {
    fn default() -> Self {
        let mut instance = Self {
            r#tab: [i32::default(); (-1000 + 1) as usize],
        };
        instance.initialisation();
        instance
    }
}
impl comparison_tabular_03 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#tab = [];
    }
}
