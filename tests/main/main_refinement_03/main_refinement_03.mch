/* main_refinement_01
 * Author: cchen4
 * Creation date: 20/06/2023
 */
MACHINE
    main_refinement_03
    
SEES 
    b2rust_types
    
ABSTRACT_VARIABLES
    abs1
    
INVARIANT 
    abs1 : INT
    
INITIALISATION 
    abs1 := 1
    
OPERATIONS 
    res <-- sum = 
    PRE
        res : rust_i8
    THEN
        res :: rust_i8
    END

END
