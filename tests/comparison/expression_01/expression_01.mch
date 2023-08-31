/* expression_01
 * Author: 
 * Creation date: 21/03/2023
 */
MACHINE
    expression_01
    
CONCRETE_VARIABLES
    value
    
INVARIANT
    value : NAT

INITIALISATION
    value := 0
    
OPERATIONS
    adding = BEGIN
        skip
    END
END