/* main_sets_04
 * Author: 
 * Creation date: 09/06/2023
 */
MACHINE
    main_sets_04

SETS
	color = {blue, white, red}
	
OPERATIONS
    it <-- return_red = PRE
        it : color
    THEN
        it := red
    END
END