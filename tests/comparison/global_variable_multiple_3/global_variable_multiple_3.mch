/* global_variable_multiple_3
 * Author: 
 * Creation date: 09/03/2023
 */
MACHINE
    global_variable_multiple_3
    
ABSTRACT_VARIABLES
    trains,
    roads,
    traffic_state
    
CONCRETE_VARIABLES
    hour
    
INVARIANT
    hour : NAT &
    trains : NAT &
    roads : NAT &
    traffic_state : BOOL
    
INITIALISATION
    hour := 14 ||
    trains := 56 ||
    roads := 26239 ||
    traffic_state := FALSE

END
