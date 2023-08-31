/* main_imports_02_01
 * Author: 
 * Creation date: 03/05/2023
 */
MACHINE
    main_imports_02_01

SEES
    b2rust_types
    
OPERATIONS
    int <-- return_one = PRE
        int : rust_i8
    THEN
        int := 1
    END
    
END
