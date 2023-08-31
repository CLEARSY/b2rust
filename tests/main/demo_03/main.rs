fn main() {
    let mut s: demo_03::demo_03 = Default::default();

    s.change_train_type_length(&2, &demo_03::trains::RER, &demo_03::longueur::train_long);

    let mut _type: demo_03::trains = Default::default();
    let mut taille: demo_03::longueur = Default::default();
    s.return_train(&2, &mut _type, &mut taille);
    assert_eq!(_type, demo_03::trains::RER);

    s.return_train(&2, &mut _type, &mut taille);
    assert_eq!(_type, demo_03::trains::RER);

    s.change_train_type_length(&1, &demo_03::trains::Transilien, &demo_03::longueur::train_long);
    s.return_train(&1, &mut _type, &mut taille);
    assert_eq!(_type, demo_03::trains::Transilien);
    assert_eq!(taille, demo_03::longueur::train_long);
}





