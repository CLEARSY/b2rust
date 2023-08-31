/* main_tabular_03
 * Author: 
 * Creation date: 25/05/2023
 */
MACHINE
    main_tabular_15

SEES
    b2rust_types,data
    
OPERATIONS
    the_tab <-- get_tab1 = PRE
        the_tab : 0..(array_length_max+1) --> rust_i32
    THEN
        skip
    END;
    
    the_tab <-- get_tab2 = PRE
        the_tab : 0..5 --> rust_i32
    THEN
        skip
    END;
    
    the_tab <-- set_tab(aa) = PRE
        the_tab : 0..5 --> rust_i32 &
        aa : rust_i32
    THEN
        skip
    END
END
