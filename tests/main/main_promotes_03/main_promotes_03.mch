/* main_promotes_03
 * Author: cchen4
 * Creation date: 07/07/2023
 */
MACHINE
    main_promotes_03
SEES
    b2rust_types
    
INCLUDES
    main_promotes_03_01
    
PROMOTES
    op_01
    
OPERATIONS
    
    res <-- op =
    PRE
        res : rust_i8
    THEN
        res :: rust_i8
    END;
    
    res <-- op_02 =
    PRE
        res : rust_i8
    THEN
        res :: rust_i8
    END
END
