/* main_oprust_05
 * Author: cchen4
 * Creation date: 01/08/2023
 */
MACHINE
    main_oprust_05
SEES
    b2rust_types
    
OPERATIONS
    
    res <-- complique(aa,bb) =
    PRE
        res : rust_i8 &
        aa : rust_u8 &
        bb : rust_u8
    THEN
        skip
    END
END
