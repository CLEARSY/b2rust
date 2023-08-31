pub struct comparison_call_01_02 {}

impl Default for comparison_call_01_02 {
    fn default() -> Self {
        let mut instance = Self {};
        instance.initialisation();
        instance
    }
}
impl comparison_call_01_02 {
    fn initialisation(&mut self) {}

    pub fn give_true(&mut self, r#boolean: &mut bool) {
        *r#boolean = true;
    }

    pub fn give_false(&mut self, r#boolean: &mut bool) {
        *r#boolean = false;
    }
}
