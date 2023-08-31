/* counter
 * Author: 
 * Creation date: 12/03/2023
 */
MACHINE
        counter
    VARIABLES
        value, overflow
    INVARIANT
        value: INT & overflow: BOOL &
        0 <= value & value <= MAXINT &
        ((overflow = TRUE) => (value = MAXINT))
    INITIALISATION
        value := 0 || overflow := FALSE
    OPERATIONS
        zero =
        BEGIN
            value := 0 || overflow := FALSE
        END;
        inc =
        PRE
            value <= MAXINT
        THEN
            IF value < MAXINT THEN
                value := value + 1
            ELSE
                overflow := TRUE
            END
        END
        // res <-- get = res := value
    END
