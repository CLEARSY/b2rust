/* expression_02
 * Author: 
 * Creation date: 11/04/2023
 */
MACHINE
    expression_02
    
CONCRETE_VARIABLES
    value
    
INVARIANT
    value : NAT

INITIALISATION
    value := 0
    
OPERATIONS
    modify = BEGIN
        IF value > 2 & value < 4 THEN
            value := (value + 7) ** (value - 2)
        END
    END
END