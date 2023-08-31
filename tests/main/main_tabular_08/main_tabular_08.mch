/* main_tabular_08
* Author: 
* Creation date: 02/06/2023
*/
MACHINE
    main_tabular_08
    
SEES
    b2rust_types
    
OPERATIONS
    reset(value1, value2) = PRE
        value1 : rust_i8 &
        0 <= value1 &
        value1 <= 2 &
        value2 : rust_i8 &
        0 <= value2 &
        value2 <= 2
    THEN
        skip
    END;
    
    the_tab <-- get_tab = PRE
        the_tab : 0..2 --> (0..2 --> rust_i8)
    THEN
        skip
    END
END