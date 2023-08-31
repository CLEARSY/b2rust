/* main_imports_04_01
 * Author: 
 * Creation date: 09/05/2023
 *
 * Test of recursive imports, with collisions, without renaming, without any call.
 */
MACHINE
    main_imports_04_01

SEES
    b2rust_types

INCLUDES
    main_imports_04_02,
    main_imports_04_03
    
    
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
