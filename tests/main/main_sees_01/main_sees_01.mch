/* main_sees_01
 * Author: cchen4
 * Creation date: 10/07/2023
 */
MACHINE
    main_sees_01

SEES b2rust_types,
     main_sees_01_02
    
INCLUDES
    
    main_sees_01_01
   
OPERATIONS
    res <-- op(aa)=
    PRE 
        aa: rust_i8   &
        res : color
    THEN
        res <-- op_02
    END
    
    ;
    
    res <-- vv_access(aa)=
    PRE 
        aa: rust_i8   &
        res : rust_i8 &
        aa >0 &
        aa< 20&
        vv >0 &
        vv < 20
    THEN
        res :: rust_i8
    END
END
