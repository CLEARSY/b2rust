/* main_boolexpr_01
 * Author: cchen4
 * Creation date: 07/08/2023
 */
MACHINE
    main_boolexpr_01

SEES
    b2rust_types
    
OPERATIONS
    res <-- is_happy = 
    PRE 
        res : BOOL
    THEN
        res :: BOOL
    END
    
END
