
/* addition
 * Author: cchen4
 * Creation date: 20/06/2023
 */
MACHINE
    main_oprust_04

SEES 
    b2rust_types,c4b_types

OPERATIONS
    res <-- lshift(aa,bb) =
    PRE 
        aa : uint8_t &
        bb : rust_u8 &
        res : rust_u8
    THEN
        res :: uint8_t
    END
    ;
        res <-- rshift(aa,bb) =
    PRE 
        aa : rust_i8 &
        bb : rust_i8 &
        res : rust_i8
    THEN
        res :: rust_i8
    END
    ;
        res <-- xor(aa,bb) =
    PRE 
        aa : rust_i8 &
        bb : rust_i8 &
        res : rust_i8
    THEN
        res :: rust_i8
    END
    ;
        res <-- orr(aa,bb) =
    PRE 
        aa : rust_i8 &
        bb : rust_i8 &
        res : rust_i8
    THEN
        res :: rust_i8
    END;
            res <-- and(aa,bb) =
    PRE 
        aa : rust_i8 &
        bb : rust_i8 &
        res : rust_i8
    THEN
        res :: rust_i8
    END
    
END