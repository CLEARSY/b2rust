/* WARNING : LCHIP system source file, do not edit */

MACHINE
    c4b_types

    
CONCRETE_CONSTANTS
    bitwise_sll_uint8,
    add_uint32,
    sub_uint32,
    fit_in_u8,

    uint8_t,
    uint16_t,
    uint32_t,
    MAX_UINT32, //not translated, because not typed
    MAX_UINT16, //not translated, because not typed
    MAX_UINT8   //not translated, because not typed
    
PROPERTIES
    MAX_UINT32 = 4294967295&  
    MAX_UINT16 = 65535 &
    MAX_UINT8 = 255 &
    uint32_t = 0..4294967295 &    //same def with rust_u32, put "uint32_t rust_u32" in    
                                  // b2rust_types.cfg, then aa : uint32_t <=> aa : rust_u32
    uint16_t = 0..65535 &
    uint8_t = 0..255 &
    
    bitwise_sll_uint8 : uint8_t*uint8_t --> uint8_t &
    add_uint32 : uint32_t*uint32_t --> uint32_t &
    sub_uint32 : uint32_t*uint32_t --> uint32_t &
    fit_in_u8 : uint8_t --> uint8_t &
    
    bitwise_sll_uint8 = %(x1,x2).(x1 : uint8_t & x2 : uint8_t | (x1 * (2**x2)) mod (MAX_UINT8 + 1)) &

    add_uint32 = %(x1,x2).(x1 : uint32_t & x2 : uint32_t | (x1 + x2) mod (MAX_UINT32 + 1)) &
    sub_uint32 = %(x1,x2).(x1 : uint32_t & x2 : uint32_t | (x1 - x2 + MAX_UINT32 + 1) mod (MAX_UINT32 + 1)) &
    
    fit_in_u8 = %(xx).(xx : uint8_t | xx) 
END



