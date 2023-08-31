/* main_module_01_01
 * Author: cchen4
 * Creation date: 22/06/2023
 
Reference manuel B : 

Contrairement aux autres modules qui sont
raffinés et peuvent être traduits, il n’est pas traduit mais doit posséder un code associé
qui implémente directement ses données et ses services
*/

MACHINE
    main_module_01_01

SEES
    b2rust_types
    
CONCRETE_CONSTANTS
    const1
    
PROPERTIES
    const1 : rust_i8
    
CONCRETE_VARIABLES
    var1 
   
INVARIANT 
    var1 : rust_i8  &
    var1 < 10 &
    var1 > -1
    
    
INITIALISATION
    var1 := 0
    


OPERATIONS
    
/*    
    Error(msg) = 
    PRE 
        msg : STRING 
    THEN
        skip
    END;
*/    
    
    res <-- getVar =
    PRE
        res : rust_i8
    THEN
    	res := var1
    END;
    
    
    res <-- addVar(vv) = 
    PRE 
        vv : rust_i8 &
        res : rust_i8 
    THEN 
        res := vv + var1
    END
    
END
