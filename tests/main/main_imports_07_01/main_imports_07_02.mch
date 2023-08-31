/* main_imports_07_02
* Author: 
* Creation date: 15/05/2023
*/
MACHINE
    main_imports_07_02
    
SEES
    b2rust_types
    
OPERATIONS
    boolean <-- is_more(value, var) = PRE
        value : rust_i32 &
        var : rust_i32 &
        boolean : rust_bool
    THEN
        IF value > var THEN
            boolean := TRUE
        ELSE
            boolean := FALSE
        END
    END
END
