/* main_assertion_01
 * Author: 
 * Creation date: 27/04/2023
 */
MACHINE
    main_unsigned_02

SEES
    b2rust_types
    
OPERATIONS
    value <-- inc(integer) = PRE
        integer : rust_u32 &
        value : rust_u32
    THEN
        IF integer <= 1000 THEN
            value := integer + 1
        ELSE
            value := 0
        END
    END
END
