/* main_tabular_04
 * Author: 
 * Creation date: 25/05/2023
 */
MACHINE
    main_tabular_04

SEES
    b2rust_types
    
OPERATIONS
    element <-- get_element(index) = PRE
        element : rust_i32 &
        index : rust_i32 &
        0 <= index &
        index <= 5
    THEN
        skip
    END
END
