/* main_imports_03_01
 * Author: 
 * Creation date: 09/05/2023
 *
 * Test of exactly one import, wwithout renaming, without any call.
 */
MACHINE
    main_imports_03_01

SEES
    b2rust_types

INCLUDES
    main_imports_03_02
    
    
ABSTRACT_VARIABLES
    var
    
INVARIANT
    var : INT
    
INITIALISATION
    var := 0
    
OPERATIONS
    inc = BEGIN
        IF var < 1000 THEN
            var := var + 1
        END
    END;
    
    value <-- get_var = PRE
        value : rust_i16
    THEN
        value := var
    END
    
    
END
