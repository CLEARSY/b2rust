/* if_2
 * Author: 
 * Creation date: 19/03/2023
 */
MACHINE
    if_2

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
        SELECT train = 12 & metro /= train THEN
            train := 2637
        WHEN metro = train THEN
            train := -60
        ELSE
            skip
        END
    END
END