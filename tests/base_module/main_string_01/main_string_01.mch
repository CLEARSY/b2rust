/* main_string_01
 * Author: cchen4
 * Creation date: 26/07/2023
 */
MACHINE
    main_string_01

SEES
    b2rust_types
    
INCLUDES
    error
    
OPERATIONS
    res <-- noOverflow(aa,bb)=
    PRE
        res : rust_i8 &
        aa : rust_i8 &
        bb : rust_i8 &
        aa >0 &
        bb >0
    THEN
        res :: rust_i8
    END
END
