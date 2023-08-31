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
    rust_u8,
    add_i8,
    sub_i8,
    mul_i8,
    div_i8,
    and_i8,
    or_i8,
    xor_i8,
    lshift_i8,
    rshift_i8


PROPERTIES
    rust_i32 = -2147483648..2147483647 &
    rust_i16 = -32768..32767 &
    rust_i8 = -128..127 &
    rust_bool = BOOL &
    rust_u32 = 0..4294967295 &
    rust_u16 = 0..65535 &
    rust_u8 = 0..255 &
    add_i8 : (rust_i8 * rust_i8) --> rust_i8   &     
    add_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a1 + a2 : rust_i8| a1 + a2) &
    
    sub_i8 : (rust_i8 * rust_i8) --> rust_i8   &     
    sub_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a1 - a2 : rust_i8| a1 - a2) &
    
    mul_i8 : (rust_i8 * rust_i8) --> rust_i8   &     
    mul_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a1 * a2 : rust_i8| a1 * a2) &
    
    div_i8 : (rust_i8 * rust_i8) --> rust_i8   &     
    div_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a2 /= 0 & a1 / a2 : rust_i8| a1 / a2) &
    
    and_i8 : (rust_i8 * rust_i8) --> rust_i8   &
    or_i8 : (rust_i8 * rust_i8) --> rust_i8 &
    xor_i8 : (rust_i8 * rust_i8) --> rust_i8 &
    lshift_i8 : (rust_i8 * rust_i8) --> rust_i8 &
    rshift_i8 : (rust_i8 * rust_i8) --> rust_i8 
    
ASSERTIONS
    dom(add_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a1 + a2 : rust_i8} &
    dom(sub_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a1 - a2 : rust_i8} &
    dom(mul_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a1 * a2 : rust_i8} &
    dom(div_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a2 /= 0 & a1 / a2 : rust_i8} 
 
END