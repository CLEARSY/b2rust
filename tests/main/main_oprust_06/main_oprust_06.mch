/* main_oprust_06
 * Author: cchen4
 * Creation date: 02/08/2023
 */
MACHINE
    main_oprust_06

SEES
    b2rust_types
    
SETS
    ANIMAL = {CAT, KITTEN, TIGGER}
    
CONCRETE_VARIABLES
    tab2
    
INVARIANT
    tab2 : rust_u8 --> ANIMAL
    
INITIALISATION
    tab2 := rust_u8 * {CAT}
    
OPERATIONS
    res <-- compliquee(aa,bb,cc,tab1) = 
    PRE
        res : ANIMAL &
        aa :  rust_i16 &
        bb : rust_u8 &
        cc : rust_i16 &
        tab1 : rust_u8 -->  rust_u8
    THEN
        skip
        
    END
END
