/* global_variable_multiple
 * Author: 
 * Creation date: 01/03/2023
 */
MACHINE
    global_variable_multiple
   
ABSTRACT_VARIABLES
    trains,
    roads,
    traffic_state
    
INVARIANT
    trains : NAT &
    roads : NAT &
    traffic_state : BOOL
    
INITIALISATION
    trains := 56 ||
    roads := 26239 ||
    traffic_state := FALSE

END
