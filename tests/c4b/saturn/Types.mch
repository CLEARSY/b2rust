/* Types
 * Author: 
 * Creation date: 04/07/14
 */
MACHINE
    Types

CONCRETE_CONSTANTS
    uint8_t,
    uint16_t,
    uint32_t,
    SBOOL,
    STRUE,
    SFALSE,
    SYNCHRONISATION ,            
    REQUETE_SECU,                
    REQUETE_NON_SECU,            
    REPONSE_SECU,                
    REPONSE_NON_SECU,            
    ATTRIBUTION_TID,             
    ATTRIBUTION_SID,             
    ACQ_ATTRIBUTION_SID,         
    REPROGRAMMATION_SECU        
    
    
PROPERTIES
    uint8_t = 0..255 &
    uint16_t = 0..65535 &
    uint32_t = 0..4294967295 &
    SBOOL = 0..255 &
    STRUE : SBOOL &
    SFALSE : SBOOL &
    STRUE /= SFALSE &
    SYNCHRONISATION :   uint8_t &         
    REQUETE_SECU :   uint8_t &                  
    REQUETE_NON_SECU :   uint8_t &              
    REPONSE_SECU :   uint8_t &                  
    REPONSE_NON_SECU :   uint8_t &              
    ATTRIBUTION_TID :   uint8_t &               
    ATTRIBUTION_SID :   uint8_t &               
    ACQ_ATTRIBUTION_SID :   uint8_t &           
    REPROGRAMMATION_SECU :   uint8_t 
    
END
