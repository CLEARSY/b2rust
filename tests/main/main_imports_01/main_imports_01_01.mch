/* main_imports_01_01
* Author: 
* Creation date: 02/05/2023
*/
MACHINE
    main_imports_01_01
    
SEES
    b2rust_types
    
OPERATIONS
    boolean <-- return_true = PRE
        boolean : rust_bool
    THEN
        boolean := TRUE
    END
    
END
