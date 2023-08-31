/* main_local_variable_01
* Author: 
* Creation date: 27/04/2023
*/
MACHINE
    main_local_variable_02
    
SEES
    b2rust_types
    
OPERATIONS
    value <-- inc(integer) = PRE
        integer : rust_i32 &
        value : rust_i32
    THEN
        IF integer <= 1000 THEN
            value := integer + 1
        ELSE
            value := 0
        END
    END
END