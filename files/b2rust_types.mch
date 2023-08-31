/* b2rust_types
 * Author: 
 * Creation date: 28/02/2023
 */
MACHINE
    b2rust_types
    
CONCRETE_CONSTANTS
    rust_i64,
    rust_i32,
    rust_i16,
    rust_i8,
    
    rust_bool,
    
    rust_u64,
    rust_u32,
    rust_u16,
    rust_u8,
    
    add_i8,
    add_i16,
    add_i32,
    add_i64,
    
    add_u8,
    add_u16,
    add_u32,
    add_u64,
    
    sub_i8,
    sub_i16,
    sub_i32,
    sub_i64,
    
    sub_u8,
    sub_u16,
    sub_u32,
    sub_u64,
    
    mul_i8,
    mul_i16,
    mul_i32,
    mul_i64,
    
    mul_u8,
    mul_u16,
    mul_u32,
    mul_u64,
    
    div_i8,
    div_i16,
    div_i32,
    div_i64,
    
    div_u8,
    div_u16,
    div_u32,
    div_u64,
    
    and_i8,
    and_i16,
    and_i32,
    and_i64,
    
    and_u8,
    and_u16,
    and_u32,
    and_u64,
    
    or_i8,
    or_i16,
    or_i32,
    or_i64,
    
    or_u8,
    or_u16,
    or_u32,
    or_u64,
    
  
    xor_i8,
    xor_i16,
    xor_i32,
    xor_i64,
    
    xor_u8,
    xor_u16,
    xor_u32,
    xor_u64,
    
    lshift_i8,
    lshift_i16,
    lshift_i32,
    lshift_i64,
    
    lshift_u8,
    lshift_u16,
    lshift_u32,
    lshift_u64,
    
    rshift_i8,
    rshift_i16,
    rshift_i32,
    rshift_i64,
    
    rshift_u8,
    rshift_u16,
    rshift_u32,
    rshift_u64,
    
    pow_i8,
    pow_i16,
    pow_i32,
    pow_i64,
    
    pow_u8,
    pow_u16,
    pow_u32,
    pow_u64,
    
    mod_i8,
    mod_i16,
    mod_i32,
    mod_i64,
    
    mod_u8,
    mod_u16,
    mod_u32,
    mod_u64,
    
    fit_i8,
    fit_i16,
    fit_i32,
    fit_i64,
    
    fit_u8,
    fit_u16,
    fit_u32,
    fit_u64,


PROPERTIES
    rust_i64 = -9223372036854775808..9223372036854775807 &
    rust_i32 = -2147483648..2147483647 &
    rust_i16 = -32768..32767 &
    rust_i8 = -128..127 &
    rust_bool = BOOL &
    rust_u64 = 0..18446744073709551615&
    rust_u32 = 0..4294967295 &
    rust_u16 = 0..65535 &
    rust_u8 = 0..255 &
    
    add_i8 : (rust_i8 * rust_i8) +-> rust_i8   &     
    add_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a1 + a2 : rust_i8| a1 + a2) &
    add_i16 : (rust_i16 * rust_i16) +-> rust_i16   &     
    add_i16 = %(a1,a2).(a1 : rust_i16 & a2 : rust_i16 & a1 + a2 : rust_i16| a1 + a2) &
    add_i32 : (rust_i32 * rust_i32) +-> rust_i32   &     
    add_i32 = %(a1,a2).(a1 : rust_i32 & a2 : rust_i32 & a1 + a2 : rust_i32| a1 + a2) &
    add_i64 : (rust_i64 * rust_i64) +-> rust_i64   &     
    add_i64 = %(a1,a2).(a1 : rust_i64 & a2 : rust_i64 & a1 + a2 : rust_i64| a1 + a2) &
    
    add_u8 : (rust_u8 * rust_u8) +-> rust_u8   &     
    add_u8 = %(a1,a2).(a1 : rust_u8 & a2 : rust_u8 & a1 + a2 : rust_u8| a1 + a2) &
    add_u16 : (rust_u16 * rust_u16) +-> rust_u16   &     
    add_u16 = %(a1,a2).(a1 : rust_u16 & a2 : rust_u16 & a1 + a2 : rust_u16| a1 + a2) &
    add_u32 : (rust_u32 * rust_u32) +-> rust_u32   &     
    add_u32 = %(a1,a2).(a1 : rust_u32 & a2 : rust_u32 & a1 + a2 : rust_u32| a1 + a2) &
    add_u64 : (rust_u64 * rust_u64) +-> rust_u64   &     
    add_u64 = %(a1,a2).(a1 : rust_u64 & a2 : rust_u64 & a1 + a2 : rust_u64| a1 + a2) &
    
    
    sub_i8 : (rust_i8 * rust_i8) +-> rust_i8   &     
    sub_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a1 - a2 : rust_i8| a1 - a2) &
    sub_i16 : (rust_i16 * rust_i16) +-> rust_i16   &     
    sub_i16 = %(a1,a2).(a1 : rust_i16 & a2 : rust_i16 & a1 - a2 : rust_i16| a1 - a2) &
    sub_i32 : (rust_i32 * rust_i32) +-> rust_i32   &     
    sub_i32 = %(a1,a2).(a1 : rust_i32 & a2 : rust_i32 & a1 - a2 : rust_i32| a1 - a2) &
    sub_i64 : (rust_i64 * rust_i64) +-> rust_i64   &     
    sub_i64 = %(a1,a2).(a1 : rust_i64 & a2 : rust_i64 & a1 - a2 : rust_i64| a1 - a2) &
    
    sub_u8 : (rust_u8 * rust_u8) +-> rust_u8   &     
    sub_u8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a1 - a2 : rust_i8| a1 - a2) &
    sub_u16 : (rust_u16 * rust_u16) +-> rust_u16   &     
    sub_u16 = %(a1,a2).(a1 : rust_u16 & a2 : rust_u16 & a1 - a2 : rust_u16| a1 - a2) &
    sub_u32 : (rust_u32 * rust_u32) +-> rust_u32   &     
    sub_u32 = %(a1,a2).(a1 : rust_u32 & a2 : rust_u32 & a1 - a2 : rust_u32| a1 - a2) &
    sub_u64 : (rust_u64 * rust_u64) +-> rust_u64   &     
    sub_u64 = %(a1,a2).(a1 : rust_u64 & a2 : rust_u64 & a1 - a2 : rust_u64| a1 - a2) &
    
    mul_i8 : (rust_i8 * rust_i8) +-> rust_i8   &     
    mul_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a1 * a2 : rust_i8| a1 * a2) &
    mul_i16 : (rust_i16 * rust_i16) +-> rust_i16   &     
    mul_i16 = %(a1,a2).(a1 : rust_i16 & a2 : rust_i16 & a1 * a2 : rust_i16| a1 * a2) &
    mul_i32 : (rust_i32 * rust_i32) +-> rust_i32   &     
    mul_i32 = %(a1,a2).(a1 : rust_i32 & a2 : rust_i32 & a1 * a2 : rust_i32| a1 * a2) &
    mul_i64 : (rust_i64 * rust_i64) +-> rust_i64   &     
    mul_i64 = %(a1,a2).(a1 : rust_i64 & a2 : rust_i64 & a1 * a2 : rust_i64| a1 * a2) &
    
    mul_u8 : (rust_u8 * rust_u8) +-> rust_u8   &     
    mul_u8 = %(a1,a2).(a1 : rust_u8 & a2 : rust_u8 & a1 * a2 : rust_u8| a1 * a2) &
    mul_u16 : (rust_u16 * rust_u16) +-> rust_u16   &     
    mul_u16 = %(a1,a2).(a1 : rust_u16 & a2 : rust_u16 & a1 * a2 : rust_u16| a1 * a2) &
    mul_u32 : (rust_u32 * rust_u32) +-> rust_u32   &     
    mul_u32 = %(a1,a2).(a1 : rust_u32 & a2 : rust_u32 & a1 * a2 : rust_u32| a1 * a2) &
    mul_u64 : (rust_u64 * rust_u64) +-> rust_i64   &     
    mul_u64 = %(a1,a2).(a1 : rust_u64 & a2 : rust_u64 & a1 * a2 : rust_u64| a1 * a2) &
    
    div_i8 : (rust_i8 * rust_i8) +-> rust_i8   &     
    div_i8 = %(a1,a2).(a1 : rust_i8 & a2 : rust_i8 & a2 /= 0 & a1 / a2 : rust_i8| a1 / a2) &
    div_i16 : (rust_i16 * rust_i16) +-> rust_i16   &     
    div_i16 = %(a1,a2).(a1 : rust_i16 & a2 : rust_i16 & a2 /= 0 & a1 / a2 : rust_i16| a1 / a2) &
    div_i32 : (rust_i32 * rust_i32) +-> rust_i32   &     
    div_i32 = %(a1,a2).(a1 : rust_i32 & a2 : rust_i32 & a2 /= 0 & a1 / a2 : rust_i32| a1 / a2) &
    div_i64 : (rust_i64 * rust_i64) +-> rust_i64   &     
    div_i64 = %(a1,a2).(a1 : rust_i64 & a2 : rust_i64 & a2 /= 0 & a1 / a2 : rust_i64| a1 / a2) & 

    div_u8 : (rust_u8 * rust_u8) +-> rust_u8   &     
    div_u8 = %(a1,a2).(a1 : rust_u8 & a2 : rust_u8 & a2 /= 0 & a1 / a2 : rust_u8| a1 / a2) &
    div_u16 : (rust_u16 * rust_u16) +-> rust_u16   &     
    div_u16 = %(a1,a2).(a1 : rust_u16 & a2 : rust_u16 & a2 /= 0 & a1 / a2 : rust_u16| a1 / a2) &
    div_u32 : (rust_u32 * rust_u32) +-> rust_u32   &     
    div_u32 = %(a1,a2).(a1 : rust_u32 & a2 : rust_u32 & a2 /= 0 & a1 / a2 : rust_u32| a1 / a2) &
    div_u64 : (rust_u64 * rust_u64) +-> rust_u64   &     
    div_u64 = %(a1,a2).(a1 : rust_u64 & a2 : rust_u64 & a2 /= 0 & a1 / a2 : rust_i64| a1 / a2) & 
    
    
    fit_i8 : rust_i8 --> rust_i8   &     
    fit_i8 = %(a1).(a1 : rust_i8 | a1 ) &
    fit_i16 : rust_i16 --> rust_i16   &     
    fit_i16 = %(a1).(a1 : rust_i16 | a1 ) &
    fit_i32 : rust_i32 --> rust_i32   &     
    fit_i32 = %(a1).(a1 : rust_i32 | a1 ) &
    fit_i64 : rust_i64 --> rust_i64   &     
    fit_i64 = %(a1).(a1 : rust_i64 | a1 ) &
    
    
    fit_u8 : rust_u8 --> rust_u8   &     
    fit_u8 = %(a1).(a1 : rust_u8 | a1 ) &
    fit_u16 : rust_u16 --> rust_u16   &     
    fit_u16 = %(a1).(a1 : rust_u16 | a1 ) &
    fit_u32 : rust_u32 --> rust_u32   &     
    fit_u32 = %(a1).(a1 : rust_u32 | a1 ) &
    fit_u64 : rust_u64 --> rust_u64   &     
    fit_u64 = %(a1).(a1 : rust_u64 | a1 ) &
    
    
    and_i8 : (rust_i8 * rust_i8) +-> rust_i8   &
    and_i16 : (rust_i16 * rust_i16) +-> rust_i16  &
    and_i32 : (rust_i32 * rust_i32) +-> rust_i32   &    
    and_i64 : (rust_i64 * rust_i64) +-> rust_i64   &    
    
    and_u8 : (rust_u8 * rust_u8) +-> rust_u8   &
    and_u16 : (rust_u16 * rust_u16) +-> rust_u16  &
    and_u32 : (rust_u32 * rust_u32) +-> rust_u32  &    
    and_u64 : (rust_u64 * rust_u64) +-> rust_u16   &   
 
    or_i8 : (rust_i8 * rust_i8) +-> rust_i8   &
    or_i16 : (rust_i16 * rust_i16) +-> rust_i16  &
    or_i32 : (rust_i32 * rust_i32) +-> rust_i32   &    
    or_i64 : (rust_i64 * rust_i64) +-> rust_i64   &    
    
    or_u8 : (rust_u8 * rust_u8) +-> rust_u8   &
    or_u16 : (rust_u16 * rust_u16) +-> rust_u16  &
    or_u32 : (rust_u32 * rust_u32) +-> rust_u32  &    
    or_u64 : (rust_u64 * rust_u64) +-> rust_u16   &   
    
    xor_i8 : (rust_i8 * rust_i8) +-> rust_i8   &
    xor_i16 : (rust_i16 * rust_i16) +-> rust_i16  &
    xor_i32 : (rust_i32 * rust_i32) +-> rust_i32   &    
    xor_i64 : (rust_i64 * rust_i64) +-> rust_i64   &    
    
    xor_u8 : (rust_u8 * rust_u8) +-> rust_u8   &
    xor_u16 : (rust_u16 * rust_u16) +-> rust_u16  &
    xor_u32 : (rust_u32 * rust_u32) +-> rust_u32  &    
    xor_u64 : (rust_u64 * rust_u64) +-> rust_u16   & 
    
    lshift_i8 : (rust_i8 * NAT) +-> rust_i8   &
    lshift_i16 : (rust_i16 * NAT) +-> rust_i16  &
    lshift_i32 : (rust_i32 * NAT) +-> rust_i32   &    
    lshift_i64 : (rust_i64 * NAT) +-> rust_i64   &    
    
    lshift_u8 : (rust_u8 * NAT) +-> rust_u8   &
    lshift_u16 : (rust_u16 * NAT) +-> rust_u16  &
    lshift_u32 : (rust_u32 * NAT) +-> rust_u32  &    
    lshift_u64 : (rust_u64 * NAT) +-> rust_u16   & 
    
    
    rshift_i8 : (rust_i8 * NAT) +-> rust_i8   &
    rshift_i16 : (rust_i16 * NAT) +-> rust_i16  &
    rshift_i32 : (rust_i32 * NAT) +-> rust_i32   &    
    rshift_i64 : (rust_i64 * NAT) +-> rust_i64   &    
    
    rshift_u8 : (rust_u8 * NAT) +-> rust_u8   &
    rshift_u16 : (rust_u16 * NAT) +-> rust_u16  &
    rshift_u32 : (rust_u32 * NAT) +-> rust_u32  &    
    rshift_u64 : (rust_u64 * NAT) +-> rust_u16   & 
    
    pow_i8 : (rust_i8 * rust_u32) +-> rust_i8   &
    pow_i16 : (rust_i16 * rust_u32) +-> rust_i16  &
    pow_i32 : (rust_i32 * rust_u32) +-> rust_i32   &    
    pow_i64 : (rust_i64 * rust_u32) +-> rust_i64   &    
    
    pow_u8 : (rust_u8 * rust_u32) +-> rust_u8   &
    pow_u16 : (rust_u16 * rust_u32) +-> rust_u16  &
    pow_u32 : (rust_u32 * rust_u32) +-> rust_u32  &    
    pow_u64 : (rust_u64 * rust_u32) +-> rust_u16   & 
    
    mod_i8 : (rust_i8 * rust_i8) +-> rust_i8 &
    mod_i16 : (rust_i16 * rust_i16) +-> rust_i16  &
    mod_i32 : (rust_i32 * rust_i32) +-> rust_i32  &
    mod_i64 : (rust_i64 * rust_i64) +-> rust_i64  &
    
    mod_u8 : (rust_u8 * rust_u8) +-> rust_u8 &
    mod_u16 : (rust_u16 * rust_u16) +-> rust_u16  &
    mod_u32 : (rust_u32 * rust_u32) +-> rust_u32 &
    mod_u64 : (rust_u64 * rust_u64) +-> rust_u64 
    
ASSERTIONS
    dom(add_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a1 + a2 : rust_i8} &
    dom(add_i16) = { a1, a2 | a1 : rust_i16 & a2 : rust_i16 & a1 + a2 : rust_i16} &
    
    dom(sub_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a1 - a2 : rust_i8} &
    dom(mul_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a1 * a2 : rust_i8} &
    dom(div_i8) = { a1, a2 | a1 : rust_i8 & a2 : rust_i8 & a2 /= 0 & a1 / a2 : rust_i8} 
 
END
