/* imported
 * Author: cchen4
 * Creation date: 31/07/2023
 */
MACHINE
    imported(param)

SEES
    b2rust_types
    

CONSTRAINTS
    param : NAT 
    
CONCRETE_CONSTANTS
    cc
    
PROPERTIES
    cc : rust_i8 

CONCRETE_VARIABLES
    cv

INVARIANT
    cv : rust_i8 
 
INITIALISATION
    cv := param
    

END
