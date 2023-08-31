/* if_4
 * Author: 
 * Creation date: 20/03/2023
 */
MACHINE
    if_4

ABSTRACT_VARIABLES
    train,
    metro
    
INVARIANT
    train : INT &
    metro : INT
    
INITIALISATION
    train := 12 ||
    metro := 62

OPERATIONS
    might_change_train = BEGIN
        IF train > metro THEN
            train := 12
        ELSE
            metro := 62
        END
    END
END