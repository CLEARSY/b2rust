/* main_imports_07_01
* Author: 
* Creation date: 15/05/2023
*
* Exactly one import, without renaming, with a call with input & output parameters.
*/
MACHINE
    main_imports_07_01
    
SEES
    b2rust_types
    
ABSTRACT_VARIABLES
    var
    
INVARIANT
    var : INT
    
INITIALISATION
    var := 12
    
OPERATIONS
    boolean <-- is_more(value) = PRE
        boolean : rust_bool &
        1 = 1 &
        value : rust_i32
    THEN
        IF value > var THEN
            boolean := TRUE
        ELSE
            boolean := FALSE
        END
    END
    
END
