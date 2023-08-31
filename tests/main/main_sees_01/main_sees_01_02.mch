/* main_sees_01_02
 * Author: cchen4
 * Creation date: 10/07/2023
 */
MACHINE
    main_sees_01_02


SETS
    color =  {blue,white,red}
    
OPERATIONS
    res <-- op_02 =
    PRE
        res : color
    THEN
        res :: color
    END
    

    
    
END
