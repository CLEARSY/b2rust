/* if_11
 * Author: 
 * Creation date: 11/04/2023
 */
MACHINE
    if_11

ABSTRACT_VARIABLES
    value,
    relation
    
INVARIANT
    value : 0..1000 &
    relation : (0..1) --> INT
    
INITIALISATION 
    value := 12 ||
    relation := {(0 |-> 2), (1 |-> 3)}

OPERATIONS
    might_change_value = BEGIN
        IF value / 2 = 6  THEN
            value := value / 2
        END
    END
    
END