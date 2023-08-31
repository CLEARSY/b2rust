/* main_imports_02
 * Author: 
 * Creation date: 03/05/2023
 *
 * Test of recursive imports, with collision, with renaming, with several instances on same module, and operation call.
 */
MACHINE
    main_imports_02

SEES
    b2rust_types
    
INCLUDES
    M1.main_imports_02_01,
    M2.main_imports_02_01,
    main_imports_02_02

OPERATIONS
    int <-- return_four = PRE
        int : rust_i8
    THEN
        int := 4
    END
    
END
