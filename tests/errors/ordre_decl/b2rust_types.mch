/* b2rust_types
 * Author: 
 * Creation date: 28/02/2023
 */
MACHINE
    b2rust_types
    
CONCRETE_CONSTANTS
    rust_i32,
    rust_i16,
    rust_i8,
    rust_bool,
    rust_u32,
    rust_u16,
    rust_u8


PROPERTIES
    rust_i32 = -2147483648..2147483647 &
    rust_i16 = -32768..32767 &
    rust_i8 = -128..127 &
    rust_bool = BOOL &
    rust_u32 = 0..4294967295 &
    rust_u16 = 0..65535 &
    rust_u8 = 0..255 
END