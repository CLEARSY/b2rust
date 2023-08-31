struct demo_01 {
    etat_i: bool,
    heure: i8,
    traffic_reduit: i16,
    trains_en_circulation: i16,
    trains_maximum: i16,
}

impl demo_01 {
    fn initialisation(&mut self) {
        self.traffic_reduit = 35;
        self.trains_maximum = 9999;
        self.trains_en_circulation = 100;
        self.heure = 0;
        self.etat_i = false;
    }

    fn ajouter_train_en_circulation(&mut self) {
        if self.trains_en_circulation < self.trains_maximum {
            self.trains_en_circulation = (self.trains_en_circulation) + (1);
        }
    }

    fn retirer_train_de_la_circulation(&mut self) {
        if self.trains_en_circulation > 0 {
            self.trains_en_circulation = (self.trains_en_circulation) - (1);
        }
    }

    fn ajuster_traffic(&mut self) {
        if self.heure < 5 {
            self.trains_en_circulation = self.traffic_reduit;
        } else {
            if self.heure > 23 {
                self.trains_en_circulation = self.traffic_reduit;
            } else {
                if self.trains_en_circulation < 100 {
                    self.trains_en_circulation = 100;
                }
            }
        }
    }

    fn reinitialiser_traffic(&mut self) {
        self.etat_i = false;
    }
}
