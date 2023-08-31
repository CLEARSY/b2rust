struct operation_06 {}

impl operation_06 {
    fn initialisation(&mut self) {}

    fn return_3_false_1024(
        &mut self,
        boolean: &mut bool,
        integer: &mut i8,
        other_integer: &mut i32,
    ) {
        *integer = 3;
        *boolean = false;
        *other_integer = 1024;
    }
}
