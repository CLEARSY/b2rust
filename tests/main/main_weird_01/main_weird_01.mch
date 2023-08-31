/* main_weird_01
 * Author: cchen4
 * Creation date: 09/08/2023
 */
MACHINE
    main_weird_01

SEES
    b2rust_types
    
SETS
    color = {BLUE,RED}
    
OPERATIONS
    res <-- op(aa) =
    PRE
        res : rust_i8 &
        aa : rust_i16
    THEN
        res :: rust_i8
    END
END
