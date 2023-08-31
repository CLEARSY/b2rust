/* if_07
 * Author: 
 * Creation date: 07/04/2023
 */
MACHINE
    if_07

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
        IF value > 0 & value < 500 THEN
            value := value * 2
        ELSIF value = 0 or value >= 500 THEN
            IF value = 0 THEN
                value := value + 1
            END
        END
    END
    
END