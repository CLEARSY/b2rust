/* operation_06
 * Author: 
 * Creation date: 24/04/2023
 */
MACHINE
    operation_06

SEES b2rust_types
    
OPERATIONS
    integer, boolean, other_integer <-- return_3_false_1024 = PRE
        boolean : rust_bool &
        2 = 2 &
        3 = 3 &
        other_integer : rust_i32 &
        integer : rust_i8 &
        4 = 4
    THEN
        integer, boolean, other_integer := 3, FALSE, 1024
    END
END
