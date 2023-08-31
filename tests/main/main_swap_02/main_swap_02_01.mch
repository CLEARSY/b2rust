/* main_swap_02_01
 * Author: cchen4
 * Creation date: 21/07/2023
 */
MACHINE
    main_swap_02_01

SEES 
    b2rust_types,empty
    
CONCRETE_VARIABLES
    xx, yy
    
INVARIANT
    xx : rust_i8 &
    yy : rust_i8
    
INITIALISATION
    xx :=  0 ||
    yy := 1

END
