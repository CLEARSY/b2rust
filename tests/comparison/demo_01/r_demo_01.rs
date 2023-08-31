use std::convert::TryFrom;

pub struct demo_01 {
    // Concrete variables.
    pub r#etat_i: bool,
    pub r#heure: i8,
    pub r#trains_en_circulation: i16,
}

impl Default for demo_01 {
    fn default() -> Self {
        let mut instance = Self {
            r#etat_i: bool::default(),
            r#heure: i8::default(),
            r#trains_en_circulation: i16::default(),
        };
        instance.initialisation();
        instance
    }
}
impl demo_01 {
    // Constant’s `VALUES`.
    pub const r#trains_maximum: i16 = 9999;
    pub const r#traffic_reduit: i16 = 35;
    fn initialisation(&mut self) {
        // `INITIALISATION` clause.
        self.r#trains_en_circulation = i16::try_from(100).unwrap();
        self.r#heure = i8::try_from(0).unwrap();
        self.r#etat_i = bool::try_from(false).unwrap();
    }

    pub fn ajouter_train_en_circulation(&mut self) {
        if self.r#trains_en_circulation < Self::r#trains_maximum {
            self.r#trains_en_circulation =
                i16::try_from(((self.r#trains_en_circulation) + (1))).unwrap();
        }
    }

    pub fn retirer_train_de_la_circulation(&mut self) {
        if self.r#trains_en_circulation > 0 {
            self.r#trains_en_circulation =
                i16::try_from(((self.r#trains_en_circulation) - (1))).unwrap();
        }
    }

    pub fn ajuster_traffic(&mut self) {
        if self.r#heure < 5 {
            self.r#trains_en_circulation = i16::try_from(Self::r#traffic_reduit).unwrap();
        } else {
            if self.r#heure > 23 {
                self.r#trains_en_circulation = i16::try_from(Self::r#traffic_reduit).unwrap();
            } else {
                if self.r#trains_en_circulation < 100 {
                    self.r#trains_en_circulation = i16::try_from(100).unwrap();
                }
            }
        }
    }

    pub fn reinitialiser_traffic(&mut self) {
        self.r#etat_i = bool::try_from(false).unwrap();
    }
}
