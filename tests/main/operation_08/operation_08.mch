/* operation_08
 * Author: 
 * Creation date: 24/04/2023
 */
MACHINE
    operation_08

SEES b2rust_types

CONCRETE_VARIABLES
    var1, var2
    
INVARIANT
    var1 : INT &
    var2 : INT
    
INITIALISATION
    var1, var2 := 0, 0
    
OPERATIONS
    boolean_r, value_r, other_value_r <-- dummy_return(boolean, value, other_value) = PRE
        boolean : rust_bool &
        value : rust_i8 &
        other_value : rust_i32 &
        boolean_r : rust_bool &
        value_r : rust_i8 &
        1 = 1 &
        other_value_r : rust_i32
    THEN
        boolean_r, value_r, other_value_r := boolean, value, other_value
    END
END