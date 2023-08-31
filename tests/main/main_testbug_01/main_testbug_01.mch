/* main_testbug_01
 * Author: cchen4
 * Creation date: 28/08/2023
 */
MACHINE
    main_testbug_01

SEES
    b2rust_types
    
CONCRETE_VARIABLES
    cv 
    
INVARIANT
    cv : rust_u8 --> rust_i8
  
  
INITIALISATION
    cv := rust_u8 * {1}
    
OPERATIONS
    res <-- ownership_bug = 
        PRE
            res : rust_u8 --> rust_i8
        THEN
            res :: rust_u8 --> rust_i8
        END
END
