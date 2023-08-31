/* demo_03
* Author: 
* Creation date: 26/06/2023
*/
MACHINE
    demo_03
    
INCLUDES
    demo_04

SEES
    b2rust_types
    
CONCRETE_VARIABLES
    type_trains,
    taille_trains
    
CONCRETE_CONSTANTS
    nombre_de_trains_max
    
PROPERTIES
    nombre_de_trains_max : NAT
    
INVARIANT
    type_trains : 0..3 --> trains &
    taille_trains : 0..3 --> longueur
//    card(taille_trains) = nombre_de_trains_max &
//    card(type_trains) = nombre_de_trains_max
    
INITIALISATION
    type_trains := {0 |-> type_non_precise, 1 |-> type_non_precise, 2 |-> type_non_precise, 3 |-> type_non_precise} ||
    taille_trains := {0 |-> taille_non_precisee, 1 |-> taille_non_precisee, 2 |-> taille_non_precisee, 3 |-> taille_non_precisee}
    
OPERATIONS
    change_train_type_length(numero, type, taille) = PRE
        numero : 0..3 &
        numero : rust_i8 &
        type : trains &
        taille : longueur
    THEN
        type_trains(numero) := type ||
        taille_trains(numero) := taille
    END;
    
    type, taille <-- return_train(numero) = PRE
        type : trains &
        taille : longueur &
        numero : rust_i8
     THEN
        type := type_trains(numero) ||
        taille := taille_trains(numero)
    END
END