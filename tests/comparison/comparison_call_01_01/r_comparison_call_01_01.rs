mod comparison_call_01_02;

use std::convert::TryFrom;

pub struct comparison_call_01_01 {
    // Instances of imported modules.
    pub _1_M1: comparison_call_01_02::comparison_call_01_02,
    pub _2_M2: comparison_call_01_02::comparison_call_01_02,

    // Concrete variables.
    pub r#false: bool,
    pub r#true: bool,
}

impl Default for comparison_call_01_01 {
    fn default() -> Self {
        let mut instance = Self {
            // Instances of imported modules initialization.
            _1_M1: Default::default(),
            _2_M2: Default::default(),
            r#false: bool::default(),
            r#true: bool::default(),
        };
        instance.initialisation();
        instance
    }
}
impl comparison_call_01_01 {
    fn initialisation(&mut self) {
        // Instances of imported modules.
        // `INITIALISATION` clause.
        {
            let mut r#outputCopy1 = self.r#true as bool;
            self._1_M1.give_true(&mut r#outputCopy1);
            self.r#true = bool::try_from(r#outputCopy1).unwrap();
        }
        {
            let mut r#outputCopy1 = self.r#false as bool;
            self._2_M2.give_false(&mut r#outputCopy1);
            self.r#false = bool::try_from(r#outputCopy1).unwrap();
        }
    }
}
