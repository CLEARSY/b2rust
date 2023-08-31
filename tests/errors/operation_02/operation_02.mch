/* operation_02
 * Author: 
 * Creation date: 20/04/2023
 */
MACHINE
    operation_02

SEES b2rust_types
    
OPERATIONS
    return_zero(entry) = PRE
        entry : rust_i32 &
        entry : rust_i8
    THEN
        skip
    END
END
