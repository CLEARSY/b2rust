/* addition
 * Author: cchen4
 * Creation date: 20/06/2023
 */
MACHINE
    main_oprust_02

SEES 
    b2rust_types

OPERATIONS
    res <-- compliquer(aa,bb) =
    PRE 
        aa : rust_i8 &
        bb : rust_i8 &
        aa < 10 &
        aa > 0 &
        bb < 10 &
        bb > 0 &
        res : rust_i8
    THEN
        res :: rust_i8
    END
END