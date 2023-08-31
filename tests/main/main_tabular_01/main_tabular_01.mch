/* main_tabular_01
* Author: 
* Creation date: 24/05/2023
*/
MACHINE
    main_tabular_01
    
SEES
    b2rust_types
    
OPERATIONS
    reset(value) = PRE
        value : rust_i8 &
        0 <= value &
        value <= 5
    THEN
        skip
    END;
    
    the_tab <-- get_tab = PRE
        the_tab : 0..5 --> rust_i32
    THEN
        skip
    END
END
