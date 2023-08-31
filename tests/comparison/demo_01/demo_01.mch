/* demo_01
 * Author: 
 * Creation date: 23/03/2023
 */
MACHINE
    demo_01
    
CONCRETE_VARIABLES
    trains_en_circulation
    
ABSTRACT_VARIABLES
    heure,
    etat
    
CONCRETE_CONSTANTS
    trains_maximum
    
ABSTRACT_CONSTANTS
    traffic_reduit

INVARIANT
    trains_en_circulation : (0 .. trains_maximum) &
    heure : (0..23) &
    etat : BOOL

PROPERTIES
    trains_maximum : NAT &
    traffic_reduit = 35
        
INITIALISATION
    trains_en_circulation := 100 ||
    heure := 0 ||
    etat := FALSE
    
OPERATIONS
    ajouter_train_en_circulation = BEGIN
        IF trains_en_circulation < trains_maximum THEN
            trains_en_circulation := trains_en_circulation + 1
        END
    END;
    
    retirer_train_de_la_circulation = BEGIN
        IF trains_en_circulation > 0 THEN
            trains_en_circulation := trains_en_circulation - 1
        END
    END;
    
    ajuster_traffic = BEGIN
        IF heure < 5 THEN
            trains_en_circulation := traffic_reduit
        ELSIF heure > 23 THEN
            trains_en_circulation := traffic_reduit
        ELSIF trains_en_circulation < 100 THEN
            trains_en_circulation := 100
        END
     END;
        
     reinitialiser_traffic = BEGIN
         etat := FALSE
     END
END
