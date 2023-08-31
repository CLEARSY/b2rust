/* operation_05
 * Author: 
 * Creation date: 24/04/2023
 */
MACHINE
    operation_05

SEES b2rust_types
    
OPERATIONS
    integer <-- return_twelve = PRE
        1 = 1 &
        2 = 2 &
        3 = 3 &
        integer : rust_i32 &
        integer : rust_i8 &
        4 = 4
    THEN
        integer := 12
    END
END
