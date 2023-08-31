/* operation_03
* Author: 
* Creation date: 24/04/2023
*/
MACHINE
    operation_03
    
OPERATIONS
    boolean <-- return_true = PRE
        1 = 1 &
        2 = 2 or
        3 = 3
    THEN
        boolean := TRUE
    END
    
END
