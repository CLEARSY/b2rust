/* operation_09
 * Author: 
 * Creation date: 25/04/2023
 */
MACHINE
    operation_09

SEES b2rust_types
    
OPERATIONS
    value_r <-- dummy_return(value) = PRE
        value : rust_i32 &
        value_r : rust_i32
    THEN
        value_r := value
    END
END