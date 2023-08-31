/* main_imports_02_02
 * Author: 
 * Creation date: 03/05/2023
 */
MACHINE
    main_imports_02_02

SEES
    b2rust_types
    
INCLUDES
    main_imports_02_01
    
OPERATIONS
    int <-- return_two = PRE
        int : rust_i8
    THEN
        int := 2
    END
    
END
