/* machine
 * Author: cchen4
 * Creation date: 28/08/2023
 */
MACHINE
    structure

SEES
    b2rust_types
    
CONCRETE_CONSTANTS
    cc1
    
CONCRETE_VARIABLES
    cv1
    
// Constants typed in properties
PROPERTIES
    cc1 : rust_u32
  
// Variables typed in invariant
INVARIANT
    cv1 : rust_i16 
  
INITIALISATION
    cv1 := 1
    
OPERATIONS
    op = skip
    
END
