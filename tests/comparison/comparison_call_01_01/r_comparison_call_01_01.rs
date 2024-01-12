mod ____Instances____;
mod comparison_call_01_02;

use ____Instances____::*;
use std::convert::TryFrom;
use std::sync::{Arc, RwLock};

pub struct comparison_call_01_01 {
    // Instances of imported modules.
    pub __M1_comparison_call_01_02: Arc<RwLock<comparison_call_01_02::comparison_call_01_02>>,
    pub __M2_comparison_call_01_02: Arc<RwLock<comparison_call_01_02::comparison_call_01_02>>,

    // Concrete variables.
    pub r#false: bool,
    pub r#true: bool,
}

impl Default for comparison_call_01_01 {
    fn default() -> Self {
        let id = ____Instances____::instanciate_comparison_call_01_02();
        ____Instances____::instanciate_comparison_call_01_02();
        let mut instance = Self {
            // Instances of imported modules initialization.
            __M1_comparison_call_01_02: ____Instances____::get_comparison_call_01_02(id)
                .get___M1_comparison_call_01_02(),
            __M2_comparison_call_01_02: ____Instances____::get_comparison_call_01_02(id)
                .get___M2_comparison_call_01_02(),
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
            {
                let tmp = self
                    .__M1_comparison_call_01_02
                    .write()
                    .unwrap()
                    .give_true(&mut r#outputCopy1);
                tmp
            }
            self.r#true = bool::try_from(r#outputCopy1).unwrap();
        }
        {
            let mut r#outputCopy1 = self.r#false as bool;
            {
                let tmp = self
                    .__M2_comparison_call_01_02
                    .write()
                    .unwrap()
                    .give_false(&mut r#outputCopy1);
                tmp
            }
            self.r#false = bool::try_from(r#outputCopy1).unwrap();
        }
    }
}
