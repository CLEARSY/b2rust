/* PMP
* Author: 
* Creation date: 07/07/14
*/
MACHINE
    PMP
SEES
    Types
    
OPERATIONS
    PMP_Init =
    skip;
    
    PMP_InitPins =
    skip;
    
    PMP_MAJCONFIGRP =
    skip;
    
    PMP_MAJConf(p_data) =
    PRE
        p_data : uint8_t
    THEN
        skip
    END;
    
    
    p_data <-- PMP_RecupConf =
    PRE 
        p_data : uint8_t
    THEN
        p_data :: uint8_t
    END;
    
     PMP_CreateTrame(p_data)=
     PRE
         p_data : uint8_t --> uint8_t
     THEN
         skip
     END
     
END
