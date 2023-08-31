/* main_type_01
 * Author: cchen4
 * Creation date: 24/07/2023
 */
MACHINE
    main_type_01
SEES
    b2rust_types
    
CONCRETE_CONSTANTS
    cc1
    
CONCRETE_VARIABLES
    cv1
    
PROPERTIES
    cc1 : rust_i32
   
INVARIANT
    cv1 : rust_u32
   
INITIALISATION
    cv1 := 0
END
