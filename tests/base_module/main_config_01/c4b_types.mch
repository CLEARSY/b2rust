/* c4b_types
 * Author: cchen4
 * Creation date: 18/07/2023
 */
MACHINE
    c4b_types

SEES
    b2rust_types
    
CONCRETE_CONSTANTS
    uint8,
    int16,
    int8
   
PROPERTIES
    uint8 = rust_u8 &
    int16 = rust_i16 &
    int8 = rust_i8
    
END
