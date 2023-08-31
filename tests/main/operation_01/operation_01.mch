/* operation_01
 * Author: 
 * Creation date: 12/04/2023
 */
MACHINE
    operation_01

SEES b2rust_types
    
OPERATIONS
    boolean <-- return_true = PRE
        boolean : rust_bool
    THEN
        boolean := TRUE
    END
END
