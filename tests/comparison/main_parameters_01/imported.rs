use std::convert::TryFrom;

pub struct imported {
    // Parameters.
    r#param: i8,
    // Concrete variables & constants.
    pub r#cv: i8,
}

impl Default for imported {
    fn default() -> Self {
        let mut instance = Self {
            r#param: i8::default(),
            r#cv: i8::default(),
        };
        instance.initialisation();
        instance
    }
}
impl imported {
    // Constant’s `VALUES`.
    pub const r#cc: i8 = 10;
    pub fn new(r#param_arg: i8) -> Self {
        let mut instance = Self {
            r#param: r#param_arg,
            r#cv: i8::default(),
        };
        instance.initialisation();
        instance
    }
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#cv = i8::try_from(self.r#param).unwrap();
    }

    pub fn sum(&mut self, r#aa: &i8, r#bb: &i8, r#dd: &i8, r#res: &mut i8) {
        *r#res = i8::try_from((((*r#aa) + (*r#bb)) + (*r#dd))).unwrap();
    }
}
