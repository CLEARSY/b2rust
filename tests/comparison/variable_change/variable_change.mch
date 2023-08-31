/* variable_change
 * Author: 
 * Creation date: 13/03/2023
 */
MACHINE
    variable_change
    
ABSTRACT_VARIABLES
    trains,
    roads,
    traffic_state
    
CONCRETE_VARIABLES
    hour
    
INVARIANT
    hour : 0..1000 &
    trains : NAT &
    roads : NAT &
    traffic_state : BOOL
    
INITIALISATION
    hour := 14 ||
    trains := 56 ||
    roads := 26239 ||
    traffic_state := FALSE

OPERATIONS
    change_me = BEGIN
        hour := 19
    END
END
