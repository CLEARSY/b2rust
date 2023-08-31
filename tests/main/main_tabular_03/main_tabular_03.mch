/* main_tabular_03
 * Author: 
 * Creation date: 25/05/2023
 */
MACHINE
    main_tabular_03

SEES
    b2rust_types
    
OPERATIONS
    the_tab <-- get_tab = PRE
        the_tab : 0..5 --> rust_i32
    THEN
        skip
    END
END
