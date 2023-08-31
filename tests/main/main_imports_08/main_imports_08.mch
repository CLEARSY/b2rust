/* main_imports_08
 * Author: cchen4
 * Creation date: 11/07/2023
 */
MACHINE
    main_imports_08
SEES 
    b2rust_types
INCLUDES
    main_imports_08_01
    
OPERATIONS
    
    res <-- op = 
    PRE
        res : rust_i8 &
        cv > 0 &
        cv < 10 &
        cc < 20 &
        cc > 0 &
        vf = 10 &
        vf < 15 &
        cf > 0 &
        cf < 11 

    THEN 
        res :: rust_i8
    END
    
END
