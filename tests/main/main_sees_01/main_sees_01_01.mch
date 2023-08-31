/* main_sees_01_01
 * Author: cchen4
 * Creation date: 10/07/2023
 */
MACHINE
    main_sees_01_01

SEES b2rust_types
    
    

    
CONCRETE_CONSTANTS
    cc
   
CONCRETE_VARIABLES
    vv
    
PROPERTIES
    cc : rust_i8
    
INVARIANT 
    vv : rust_i8
    
INITIALISATION 
    vv := 10
    
    
OPERATIONS
    res <-- op_01 =
    PRE 
        res : rust_i8 &
        vv < 20 &
        vv >0
    THEN
        res :: rust_i8
    END;
    
    set_vv(aa) =
    PRE
        aa: rust_i8 
    THEN
        vv:=aa
    END
    
END
