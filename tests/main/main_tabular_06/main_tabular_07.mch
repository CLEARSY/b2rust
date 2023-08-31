/* main_tabular_07
 * Author: 
 * Creation date: 01/06/2023
 */
MACHINE
    main_tabular_07

SEES
    b2rust_types
    
OPERATIONS
    boolean <-- return_true = PRE
        boolean : rust_bool
    THEN
        boolean := TRUE
    END
END
