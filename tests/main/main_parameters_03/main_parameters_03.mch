/* main_parameters_01
 * Author: cchen4
 * Creation date: 31/07/2023
 */
MACHINE
    main_parameters_03(toto)

CONSTRAINTS
    toto : INT
    
SEES b2rust_types
    
    
INCLUDES
    M1.imported(10),
    M2.imported(15),
    M3.imported(5)
OPERATIONS
    res <-- total = 
    PRE
        res : rust_i8 
    THEN
        skip
    END
END
