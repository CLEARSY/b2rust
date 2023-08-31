/* operation_07
* Author: 
* Creation date: 24/04/2023
*/
MACHINE
    operation_07
    
    
SEES b2rust_types
    
OPERATIONS
    dummy_function(boolean, value, other_value) = PRE
        boolean : rust_bool &
        1 /= 2 &
        other_value : rust_i32 &
        value : rust_i8
    THEN
        skip
    END
END
