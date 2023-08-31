/* main_promotes_03_02
 * Author: cchen4
 * Creation date: 07/07/2023
 */
MACHINE
    main_promotes_04_02
SEES
    b2rust_types
OPERATIONS
    res <-- op_02 = 
    PRE
        res : rust_i8
    THEN
        res :: rust_i8
    END
END