/* main_refinement_02
 * Author: cchen4
 * Creation date: 20/06/2023
 */
MACHINE
    main_refinement_02

SEES 
    b2rust_types
    
CONCRETE_CONSTANTS
    cons1

PROPERTIES
    cons1 : rust_i8 
    
CONCRETE_VARIABLES
    var1
      
INVARIANT
    var1 : rust_i8 
    
INITIALISATION 
    var1 := 2
END
