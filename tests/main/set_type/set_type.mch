/* set_type
 * Author: cchen4
 * Creation date: 21/08/2023
 */
MACHINE
    set_type

SEES
    b2rust_types
    
SETS
    CAT = {MaineCoon, Siamese, Tiger}
    
CONCRETE_CONSTANTS
    cc, tabCat
    
PROPERTIES
    cc : CAT &
    tabCat : 0..5 --> CAT
    

   

END
