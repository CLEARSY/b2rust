/* main_imports_03_03_i
 * Author: cchen4
 * Creation date: 07/07/2023
 */

MACHINE main_promotes_04_03

SEES
    b2rust_types
    
   
OPERATIONS
    res <-- op_03a(aa) =
    PRE
        res : rust_i8 &
        aa : rust_i8
       THEN
           res :: rust_i8
    END;
    
    res <-- op_03b = 
    PRE
        res : rust_i8
    THEN 
        res :: rust_i8
    END
    
 END