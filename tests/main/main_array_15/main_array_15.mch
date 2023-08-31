/* main_array_15
 * Author: cchen4
 * Creation date: 12/08/2023
 */
MACHINE
    main_array_15
  
SEES
    b2rust_types
    
CONCRETE_CONSTANTS
    tab, tab_size
    
PROPERTIES
    tab_size  : rust_u8 &
    tab : (0..1) --> ((0..tab_size) * rust_u8  -->  rust_i8)
    
    

END
