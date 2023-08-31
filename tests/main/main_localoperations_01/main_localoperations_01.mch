/* main_localoperatio_01
 * Author: cchen4
 * Creation date: 19/07/2023
 */
MACHINE
    main_localoperations_01

SEES 
    b2rust_types
    
CONCRETE_VARIABLES
    cv

INVARIANT 
    cv : rust_i8
    
INITIALISATION
    cv := 0

    
OPERATIONS
    res <-- addWithCv(vv) =
    PRE
        res : rust_i8 &
        vv : rust_i8
    THEN
        res :: rust_i8
    END
    
    ;
    
    inc10 =
    PRE 
        cv < 50
    THEN
        cv := cv + 10
    END
    
END