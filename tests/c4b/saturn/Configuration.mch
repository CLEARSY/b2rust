/* configuration
 * Author: 
 * Creation date: 04/07/14
 */
MACHINE
    Configuration
SEES
    Types
ABSTRACT_VARIABLES
    iTempoCompteurConf
    
INVARIANT
    iTempoCompteurConf : uint16_t 
    
INITIALISATION
    iTempoCompteurConf := 0  
OPERATIONS
    Configuration_Init=
    BEGIN
        iTempoCompteurConf := 0
    END
    ;
    
    Configuration_TimerIntB =
    BEGIN
        IF iTempoCompteurConf > 0 THEN iTempoCompteurConf := iTempoCompteurConf - 1 END    
    END;
    
    p_out <-- Configuration_DecouverteReseau =
    PRE
        p_out : SBOOL &
        iTempoCompteurConf : uint16_t
    THEN
        p_out :: SBOOL ||
        iTempoCompteurConf :: uint16_t
    END
END
