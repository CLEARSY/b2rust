/* demo_04
 * Author: 
 * Creation date: 26/06/2023
 */
MACHINE
    demo_04

SETS
    trains = {metro, RER, Transilien, type_non_precise};
    longueur = {train_court, train_long, taille_non_precisee}

OPERATIONS
    type, taille <-- return_default_train = PRE
        type : trains &
        taille : longueur
    THEN
        type :: trains ||
        taille :: longueur
    END
    
    
END
