/* atomic_type
 * Author: cchen4
 * Creation date: 21/08/2023
 */
MACHINE
    atomic_type

SEES
    b2rust_types
    
CONCRETE_CONSTANTS
    cc1,cc2
    
CONCRETE_VARIABLES
    cv1
    
// Constants typed in properties
PROPERTIES
    cc1 : rust_u32 &
    cc2 : rust_bool
  
// Variables typed in invariant
INVARIANT
    cv1 : rust_i16 
  
INITIALISATION
    cv1 := 1
    
END
