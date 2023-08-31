/* variable_change_2
 * Author: 
 * Creation date: 13/03/2023
 */
MACHINE
    variable_change_2
    
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
        hour := 19 ||
        traffic_state := TRUE ||
        trains := 22
    END
END