/* main_tabular_11
 * Author: cchen4
 * Creation date: 26/07/2023
 */
MACHINE
    main_tabular_11
SEES
    b2rust_types
    
OPERATIONS
    tab <-- setValue(index,value) =
    PRE
        tab : rust_u8 --> rust_u8 &
        index : rust_u8 &
        value : rust_u8
    THEN
        tab(index) := value
    END
END
