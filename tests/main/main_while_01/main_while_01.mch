/* main_while_01
* Author: 
* Creation date: 02/05/2023
*/
MACHINE
    main_while_01
    
SEES
    b2rust_types
    
OPERATIONS
    result <-- sum(integer) = PRE
        integer : rust_i16 &
        result : rust_i16 &
        integer >= 1
    THEN
        result :: NAT
    END
    
END
