/* main_imports_05_01
 * Author: 
 * Creation date: 10/05/2023
 *
 * Test of recursive imports, with collisions, with renaming, without several instances with same name, without any call.
 */
MACHINE
    main_imports_05_01

SEES
    b2rust_types

INCLUDES
    M1.main_imports_05_02,
    M2.main_imports_05_03
    
    
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
