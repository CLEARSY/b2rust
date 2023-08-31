use std::convert::TryFrom;

#[derive(Clone, Copy, Default, Debug, Eq, PartialEq)]
pub enum ANIMAL {
    #[default]
    CAT,
    DOG,
}

#[derive(Clone, Copy, Default, Debug, Eq, PartialEq)]
pub enum COLORS {
    #[default]
    BLUE,
    WHITE,
    RED,
}

#[derive(Clone, Copy, Default, Debug, Eq, PartialEq)]
pub enum GENDER {
    #[default]
    MALE,
    FEMALE,
}

#[derive(Clone, Copy, Default, Debug, Eq, PartialEq)]
pub enum GAME {
    #[default]
    FPS,
    RPG,
}

pub struct main_set_04 {
    // Concrete variables.
    pub r#cv: ANIMAL,
    pub r#cv2: GENDER,
}

impl Default for main_set_04 {
    fn default() -> Self {
        let mut instance = Self {
            r#cv: ANIMAL::default(),
            r#cv2: GENDER::default(),
        };
        instance.initialisation();
        instance
    }
}
impl main_set_04 {
    // Constant’s `VALUES`.
    pub const r#cc: COLORS = COLORS::RED;
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#cv2 = GENDER::try_from(GENDER::FEMALE).unwrap();
        self.r#cv = ANIMAL::try_from(ANIMAL::CAT).unwrap();
    }
}
