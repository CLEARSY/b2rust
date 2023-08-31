/* precompil
 * Author: 
 * Creation date: 04/07/14
 */
MACHINE
    Precompil
SEES
    Types
OPERATIONS
    Precompil_CrcInit =
    skip;
    
    Precompil_CRCCreateB(p_trame,p_size) =
    PRE
        p_trame : uint8_t --> uint8_t &
        p_size : uint8_t
    THEN
        skip 
    END
    
END
