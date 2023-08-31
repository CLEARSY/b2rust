/* main_parameters_01
 * Author: cchen4
 * Creation date: 31/07/2023
 */
MACHINE
    main_parameters_01

SEES b2rust_types
    
    
INCLUDES
    M1.imported(10),
    M2.imported(15)
    
OPERATIONS
    res <-- total = 
    PRE
        res : rust_i8 
    THEN
        skip
    END;
    
    res <-- sum(aa,bb,dd) = 
    PRE
        res : rust_i8 &
        aa : rust_i8 &
        bb : rust_i8 &
        dd : rust_i8
    THEN
        skip
    END
END
