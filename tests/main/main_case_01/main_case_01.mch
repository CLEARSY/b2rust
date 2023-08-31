/* Switch
 * Author: spare
 * Creation date: 13/06/2023
 */
MACHINE
    main_case_01

SEES
    b2rust_types


OPERATIONS

    res <-- meilleur ( jour ) =
    PRE
        jour : rust_i8 &
        res : rust_bool
    THEN
        res :: rust_bool
    END



END
