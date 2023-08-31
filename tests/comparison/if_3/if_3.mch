/* if_3
 * Author: 
 * Creation date: 19/03/2023
 */
MACHINE
    if_3

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
        SELECT train > metro THEN
            train := 12
        END
    END
END