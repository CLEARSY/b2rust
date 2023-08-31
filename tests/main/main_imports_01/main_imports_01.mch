/* main_imports_01
* Author: 
* Creation date: 02/05/2023
*
* Test of exactly one import, with renaming, and operation call.
*/
MACHINE
    main_imports_01
    
SEES
    b2rust_types
    
INCLUDES
    M1.main_imports_01_01
    
OPERATIONS
    boolean <-- return_true = PRE
        boolean : rust_bool
    THEN
        boolean <-- M1.return_true
    END
    
END
