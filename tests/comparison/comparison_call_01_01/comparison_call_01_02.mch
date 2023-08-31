/* comparison_call_01_02
 * Author: 
 * Creation date: 22/05/2023
 */
MACHINE
    comparison_call_01_02

SEES
    b2rust_types
    
OPERATIONS
    boolean <-- give_true = PRE
        boolean : rust_bool
    THEN
        boolean := TRUE
    END;
    
    boolean <-- give_false = PRE
        boolean : rust_bool
    THEN
        boolean := FALSE
    END  
END
