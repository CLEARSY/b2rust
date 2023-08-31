
/* addition
 * Author: cchen4
 * Creation date: 20/06/2023
 */
MACHINE
    oprust_types

SEES 
    b2rust_types,c4b_types

OPERATIONS
    res <-- lshift(aa,bb) =
    PRE 
        // uint8_t type is not recognised by b2rust, 
        // unless it has an association with a type of          
        // b2rust_types, check b2rust_types.cfg 
        aa : uint8_t & 
      
        bb : rust_u8 &
        res : rust_u8
    THEN
        res :: uint8_t
    END
    
END



