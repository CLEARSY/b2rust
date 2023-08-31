/* SPI
 * Author: 
 * Creation date: 04/07/14
 */
MACHINE
    SPI
SEES
    Types
OPERATIONS
    
    SPI_Init = 
    skip;
    
    SPI_InitPins =
    skip;
    
    p_out <-- SPI_SendTrame = 
    PRE
        p_out : SBOOL
    THEN
        skip
    END
    ;
    
    p_out <-- SPI_RecuperationTrame = 
   PRE
        p_out : SBOOL
    THEN
        skip
    END
    
END
