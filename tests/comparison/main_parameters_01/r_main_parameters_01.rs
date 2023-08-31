mod imported;

use std::convert::TryFrom;

pub struct main_parameters_01 {
    // Instances of imported modules.
    pub _1_M1: imported::imported,
    pub _2_M2: imported::imported,
    pub _3_imported: imported::imported,
}

impl Default for main_parameters_01 {
    fn default() -> Self {
        let mut instance = Self {
            // Instances of imported modules initialization.
            _1_M1: Default::default(),
            _2_M2: Default::default(),
            _3_imported: Default::default(),
        };
        instance.initialisation();
        instance
    }
}
impl main_parameters_01 {
    fn initialisation(&mut self) {
        // Instances of imported modules.
        self._1_M1 = imported::imported::new(10);
        self._2_M2 = imported::imported::new(15);
        self._3_imported = imported::imported::new(5);
    }

    pub fn sum(&mut self, r#aa: &i8, r#bb: &i8, r#dd: &i8, r#res: &mut i8) {
        self._3_imported.sum(r#aa, r#bb, r#dd, r#res);
    }

    pub fn total(&mut self, r#res: &mut i8) {
        {
            let mut r#inputCopy1 = self._2_M2.r#cv as i8;
            let mut r#inputCopy2 = self._1_M1.r#cv as i8;
            let mut r#inputCopy3 = 5 as i8;
            let mut r#outputCopy1 = *r#res as i8;
            self._2_M2.sum(
                &r#inputCopy1,
                &r#inputCopy2,
                &r#inputCopy3,
                &mut r#outputCopy1,
            );
            *r#res = i8::try_from(r#outputCopy1).unwrap();
        }
    }
}
