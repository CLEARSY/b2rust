/* main_promotes_03_01
 * Author: cchen4
 * Creation date: 07/07/2023
 */
MACHINE
    main_promotes_05_01
SEES
    b2rust_types
OPERATIONS
    res <-- op_01 = 
    PRE
        res : rust_i8
    THEN
        res :: rust_i8
    END
    
END