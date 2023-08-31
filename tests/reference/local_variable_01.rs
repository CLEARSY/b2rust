struct local_variable_01 {}

impl local_variable_01 {
    fn initialisation(&mut self) {}

    fn dummy_function(&mut self) {
        {
            let mut locale: bool;
            locale = true;
            locale = false;
            {
                let mut locale2: bool;
                locale2 = locale;
                {
                    let mut locale4: bool;
                    locale4 = locale2;
                }
                locale = locale2;
            }
            locale = true;
        }
    }
}
