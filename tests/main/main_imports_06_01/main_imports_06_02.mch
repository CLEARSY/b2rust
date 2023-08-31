/* main_imports_06_02
* Author: 
* Creation date: 22/05/2023
*/
MACHINE
    main_imports_06_02

SEES
    b2rust_types
    
OPERATIONS
    boolean <-- give_true = PRE
        boolean : rust_bool
    THEN
        boolean := TRUE
    END;
    
    boolean <-- give_false = PRE
        boolean : rust_bool
    THEN
        boolean := FALSE
    END;
    
    true, false <-- give_true_and_false = PRE
        true : rust_bool &
        false : rust_bool
    THEN
        true, false := TRUE, FALSE
    END     
END
