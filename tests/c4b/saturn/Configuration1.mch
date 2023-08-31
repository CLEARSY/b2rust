/* Configuration1
 * Author: 
 * Creation date: 10/07/14
 */
MACHINE
    Configuration1
SEES 
    Types
OPERATIONS

    p_out <-- Configuration1_LANSCAN = 
    PRE
        p_out : SBOOL
    THEN
        p_out :: SBOOL
    END
    
END
