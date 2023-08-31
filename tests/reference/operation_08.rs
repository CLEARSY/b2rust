struct operation_08 {
    var1: i32,
    var2: i8,
}

impl operation_08 {
    fn initialisation(&mut self) {
        self.var1 = 0;
        self.var2 = 0;
    }

    fn dummy_return(
        &mut self,
        boolean: &bool,
        other_value: &i32,
        value: &i8,
        boolean_r: &mut bool,
        other_value_r: &mut i32,
        value_r: &mut i8,
    ) {
        self.var1 = *other_value;
        {
            let mut locale: i32;
            locale = self.var1;
            *other_value_r = locale;
        }
        *boolean_r = *boolean;
        *value_r = *value;
    }
}
