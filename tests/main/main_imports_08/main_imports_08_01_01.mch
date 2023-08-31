/* main_imports_08_01_01
 * Author: cchen4
 * Creation date: 11/07/2023
 */
MACHINE
    main_imports_08_01_01


SEES b2rust_types
    
CONCRETE_CONSTANTS
    cf
 
CONCRETE_VARIABLES
    vf
    
PROPERTIES
    cf : rust_i8
    
INVARIANT 
    vf : rust_i8
   
   
INITIALISATION
    vf := 10 
    
    
    
END
