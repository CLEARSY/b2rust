/* main_operations_01_01
* Author: 
* Creation date: 17/05/2023
*/
MACHINE
    main_operations_01_01
    
SEES
    b2rust_types
    
OPERATIONS
    boolean <-- return_opposite(entry) = PRE
        entry : rust_bool &
        boolean : rust_bool
    THEN
        IF entry = TRUE THEN
            boolean := FALSE
        ELSE
            boolean := TRUE
        END
    END;
    
    two <-- return_two = PRE
        two : rust_i8
    THEN
        two := 2
    END
END
