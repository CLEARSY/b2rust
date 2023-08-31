/* main_module_01
 * Author: cchen4
 * Creation date: 22/06/2023
 */
MACHINE
    main_module_01

SEES
    b2rust_types

OPERATIONS
    res <--sum(aa,bb)= 
    PRE
        aa : rust_i8 &
        bb : rust_i8 &
        res : rust_i8
    THEN 
        res :: rust_i8
    END
END
