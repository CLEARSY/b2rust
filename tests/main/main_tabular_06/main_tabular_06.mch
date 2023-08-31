/* main_tabular_06
* Author: 
* Creation date: 01/06/2023
*/
MACHINE
    main_tabular_06
    
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
        the_tab : 0..5--> rust_bool
    THEN
        skip
    END
    
END
