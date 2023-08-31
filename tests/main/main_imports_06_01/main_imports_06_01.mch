/* main_imports_06_01
* Author: 
* Creation date: 22/05/2023
* Compared to other tests: it test multiple return values & operations call in initialization.
*/
MACHINE
    main_imports_06_01
    
SEES
    b2rust_types
    
OPERATIONS
    reset = skip;
    
    bool_true <-- return_var_true = PRE
        bool_true : rust_bool
    THEN
        bool_true := TRUE
    END;
    
    bool_false <-- return_var_false = PRE
        bool_false : rust_bool
    THEN
        bool_false := FALSE
    END;
    
    set_true_false_to(set_true, set_false) = PRE
        set_true : rust_bool &
        set_false : rust_bool
    THEN
        skip
    END
END
