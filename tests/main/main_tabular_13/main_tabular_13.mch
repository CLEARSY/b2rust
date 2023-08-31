/* tab13
 * Author: cchen4
 * Creation date: 27/07/2023
 */
MACHINE
    main_tabular_13

SEES b2rust_types
    
OPERATIONS
   res <-- access(aa,bb) = 
        PRE 
            aa : rust_u8 &
            bb : rust_u8 &
            res : rust_i32
        THEN
            skip
        END
END
