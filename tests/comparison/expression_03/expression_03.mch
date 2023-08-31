/* expression_03
 * Author: 
 * Creation date: 11/04/2023
 */
MACHINE
    expression_03
    
CONCRETE_VARIABLES
    value
    
INVARIANT
    value : NAT

INITIALISATION
    value := 0
    
OPERATIONS
    modify = BEGIN
        value := value mod 10
    END;
    
    modify_again = BEGIN
        value := (value + 67) mod (value * 2 / 2)
    END
END