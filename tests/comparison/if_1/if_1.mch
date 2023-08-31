/* if_1
 * Author: 
 * Creation date: 13/03/2023
 */
MACHINE
    if_1
    
ABSTRACT_VARIABLES
    train
    
INVARIANT
    train : INT
    
INITIALISATION
    train := 12

OPERATIONS
    might_change_train = BEGIN
        IF 1 = 1 THEN
            train := -60
        END
    END
END