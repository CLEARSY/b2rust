/* expression_04
 * Author: 
 * Creation date: 11/04/2023
 */
MACHINE
    expression_04
    
CONCRETE_VARIABLES
    value
    
INVARIANT
    value : NAT

INITIALISATION
    value := 0
    
OPERATIONS
    modify = BEGIN
        value := value * (2 + 2)
    END
END