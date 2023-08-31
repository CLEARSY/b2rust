/* main_case_04
 * Author: 
 * Creation date: 27/06/2023
 */
MACHINE
    main_case_05

SEES
    b2rust_types
    
OPERATIONS

    res <-- meilleur ( jour ) =
    PRE
        jour : rust_i8 &
        res : rust_bool
    THEN
        res :: rust_bool
    END
END
