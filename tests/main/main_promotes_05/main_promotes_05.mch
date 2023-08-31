/* main_promotes_03
 * Author: cchen4
 * Creation date: 07/07/2023
 */
MACHINE
    main_promotes_05
SEES
    b2rust_types
    
INCLUDES
    m1.main_promotes_05_01
    
PROMOTES
    m1.op_01
    
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