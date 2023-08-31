/* if_05
 * Author: 
 * Creation date: 22/03/2023
 */
MACHINE
    if_05

ABSTRACT_VARIABLES
    value
    
INVARIANT
    value : 0..1000
    
INITIALISATION
    value := 12

OPERATIONS
    might_change_value = BEGIN
        IF value < 1000 THEN
            value := value + 1
        ELSIF value > 0 THEN
            value := value - 1
        END
    END
    
END
