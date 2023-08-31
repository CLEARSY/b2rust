/* main_sets_01
 * Author: 
 * Creation date: 09/06/2023
 */
MACHINE
    main_sets_01

SETS
    color = {blue, white, red}
    
OPERATIONS
    it <-- return_red = PRE
        it : color
    THEN
        it := red
    END
END
