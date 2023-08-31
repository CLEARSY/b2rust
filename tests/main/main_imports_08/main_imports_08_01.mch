/* main_imports_08_01
 * Author: cchen4
 * Creation date: 11/07/2023
 */
MACHINE
    main_imports_08_01

SEES 
    b2rust_types
    
    
INCLUDES
    main_imports_08_01_01
    
CONCRETE_CONSTANTS
    cc
 
CONCRETE_VARIABLES
    cv
    
PROPERTIES
    cc : rust_i8
    
INVARIANT 
    cv : rust_i8
   
   
INITIALISATION
    cv := 10 
    
    
    
END
