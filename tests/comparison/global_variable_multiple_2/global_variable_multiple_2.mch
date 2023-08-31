/* global_variable_multiple_2
 * Author: 
 * Creation date: 09/03/2023
 */
MACHINE
    global_variable_multiple_2
    
ABSTRACT_VARIABLES
    OuiGo,
    trains
    
INVARIANT
    OuiGo : NAT &
    trains : NAT
    
INITIALISATION
    trains := 56 ||
    OuiGo := 56

END
