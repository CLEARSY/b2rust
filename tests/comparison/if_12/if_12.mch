/* if_12
 * Author: 
 * Creation date: 11/04/2023
 */
MACHINE
    if_12

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
        IF value ** (value + 3 / 2) = 10  THEN
            skip
        END
    END
    
END