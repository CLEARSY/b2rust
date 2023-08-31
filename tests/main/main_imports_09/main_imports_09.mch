/* main_imports_09
 * Author: cchen4
 * Creation date: 31/07/2023
 */
MACHINE
    main_imports_09

SEES b2rust_types
    
    
INCLUDES
    M1.imported,
    M2.imported,
    M3.imported
OPERATIONS
    res <-- total = 
    PRE
        res : rust_i8 
    THEN
        skip
    END
END
