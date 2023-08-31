/* traitement
* Author: 
* Creation date: 04/07/14
*/
MACHINE
    Traitement
SEES
    Types
ABSTRACT_VARIABLES
    iTempoCompteurCyc,
    iTempoLastSynchro,
    iTempoCompteurCycSup,  
    iTempoCompteurCycInf
    
INVARIANT
    iTempoCompteurCyc : uint16_t &
    iTempoLastSynchro : uint16_t &
    iTempoCompteurCycSup : uint16_t &
    iTempoCompteurCycInf : uint16_t 
    
INITIALISATION
    iTempoCompteurCyc := 0 ||   
    iTempoLastSynchro := 0 ||
    iTempoCompteurCycSup := 0 ||
    iTempoCompteurCycInf := 0
    
OPERATIONS
    Traitement_Init =
    BEGIN
        iTempoCompteurCyc := 0 ||   
        iTempoLastSynchro := 0 ||
        iTempoCompteurCycSup := 0 ||
        iTempoCompteurCycInf := 0
    END;
    
    Traitement_InitPins =
    skip;
    
    Traitement_Trame = 
    skip;
    
    Traitement_TimerIntB =
    BEGIN
        IF iTempoCompteurCyc > 0 THEN iTempoCompteurCyc := iTempoCompteurCyc - 1 END ||
        IF iTempoLastSynchro > 0 THEN iTempoLastSynchro := iTempoLastSynchro - 1 END ||
        IF iTempoCompteurCycSup > 0 THEN iTempoCompteurCycSup := iTempoCompteurCycSup - 1 END ||
        IF iTempoCompteurCycInf > 0 THEN iTempoCompteurCycInf := iTempoCompteurCycInf - 1 END    
    END;
    
    tempo <-- Traitement_GetTempoCompteurCyc =
    PRE 
        tempo : uint16_t
    THEN
        tempo := iTempoCompteurCyc
    END;
    
    tempo <-- Traitement_GetTempoLastSynchro =
    PRE 
        tempo : uint16_t
    THEN
        tempo := iTempoLastSynchro
    END;
    tempo <-- Timers_GetTempoCompteurCycInf =
    PRE 
        tempo : uint16_t
    THEN
        tempo := iTempoCompteurCycInf
    END;
    
    tempo <-- Timers_GetTempoCompteurCycSup =
       PRE 
        tempo : uint16_t
    THEN
        tempo := iTempoCompteurCycSup
    END;
    
    Traitement_MAJFinDeCycle = 
    skip;
    
    Traitement_MAJFinDeSync =
    skip;
    
    Traitement_MAJFinDeReq = 
    skip;
    
    Traitement_VerifStatusFPGA =
    skip;
    
    Traitement_SetTempoCompteurCyc(tempo) =
    PRE
        tempo : uint16_t
    THEN
        iTempoCompteurCyc := tempo
    END;
    
    Traitement_SetTempoLastSynchro(tempo)=
    PRE
        tempo : uint16_t
    THEN
        iTempoLastSynchro := tempo
    END;
    
    Timers_SetTempoCompteurCycInf(tempo) =
    PRE
        tempo : uint16_t
    THEN
        iTempoCompteurCycInf := tempo
    END;
    
    Timers_SetTempoCompteurCycSup(tempo) =
    PRE
        tempo : uint16_t
    THEN
        iTempoCompteurCycSup := tempo
    END
END
