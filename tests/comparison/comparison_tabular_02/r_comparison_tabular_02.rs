use std::convert::TryFrom;

pub struct comparison_tabular_02 {
    // Concrete variables.
    pub r#tab: [[i32; (3 + 1) as usize]; (1 + 1) as usize],
    pub r#tab2: [[[i8; (2 + 1) as usize]; (1 + 1) as usize]; (2 + 1) as usize],
}

impl Default for comparison_tabular_02 {
    fn default() -> Self {
        let mut instance = Self {
            r#tab: [[i32::default(); (3 + 1) as usize]; (1 + 1) as usize],
            r#tab2: [[[i8::default(); (2 + 1) as usize]; (1 + 1) as usize]; (2 + 1) as usize],
        };
        instance.initialisation();
        instance
    }
}
impl comparison_tabular_02 {
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#tab = [[3615, 2, 3630, 0], [0, 0, -6, 0]];
        self.r#tab2 = [
            [[76, 1, -56], [2, 2, 2]],
            [[76, 1, -56], [2, 2, 2]],
            [[76, 1, -56], [2, 2, 2]],
        ];
    }
}
