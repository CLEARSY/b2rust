mod ____Instances____;
mod imported;

use ____Instances____::*;
use std::convert::TryFrom;
use std::sync::{Arc, RwLock};

pub struct main_parameters_01 {
    // Instances of imported modules.
    pub __M1_imported: Arc<RwLock<imported::imported>>,
    pub __M2_imported: Arc<RwLock<imported::imported>>,
    pub __imported: Arc<RwLock<imported::imported>>,
}

impl Default for main_parameters_01 {
    fn default() -> Self {
        let id = ____Instances____::instanciate_imported();
        ____Instances____::instanciate_imported();
        ____Instances____::instanciate_imported();
        let mut instance = Self {
            // Instances of imported modules initialization.
            __M1_imported: ____Instances____::get_imported(id).get___M1_imported(),
            __M2_imported: ____Instances____::get_imported(id).get___M2_imported(),
            __imported: ____Instances____::get_imported(id).get___imported(),
        };
        instance.initialisation();
        instance
    }
}
impl main_parameters_01 {
    fn initialisation(&mut self) {
        // Instances of imported modules.
        self.__M1_imported.write().unwrap().set_parameters(10);
        self.__M2_imported.write().unwrap().set_parameters(15);
        self.__imported.write().unwrap().set_parameters(5);
    }

    pub fn sum(&mut self, r#aa: &i8, r#bb: &i8, r#dd: &i8, r#res: &mut i8) {
        {
            let tmp = self
                .__imported
                .write()
                .unwrap()
                .sum(r#aa, r#bb, r#dd, r#res);
            tmp
        }
    }

    pub fn total(&mut self, r#res: &mut i8) {
        {
            let mut r#inputCopy1 = self.__M2_imported.read().unwrap().r#cv as i8;
            let mut r#inputCopy2 = self.__M1_imported.read().unwrap().r#cv as i8;
            let mut r#inputCopy3 = 5 as i8;
            let mut r#outputCopy1 = *r#res as i8;
            {
                let tmp = self.__M2_imported.write().unwrap().sum(
                    &r#inputCopy1,
                    &r#inputCopy2,
                    &r#inputCopy3,
                    &mut r#outputCopy1,
                );
                tmp
            }
            *r#res = i8::try_from(r#outputCopy1).unwrap();
        }
    }
}
