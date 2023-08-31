/* main_oprust_07
 * Author: cchen4
 * Creation date: 03/08/2023
 */
MACHINE
    main_oprust_07

SEES   
    b2rust_types

OPERATIONS
    res <-- som(aa,bb,cc) =
    PRE
        res : rust_i8 &
        aa : rust_i8 &
        bb : rust_i8 &
        cc : rust_i8 &
        aa < 100 &
        aa > -100 &
        bb < 100 &
        bb > -100
    THEN
        res :: rust_i8
    END
    
END
