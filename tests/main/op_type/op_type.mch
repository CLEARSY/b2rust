MACHINE
    op_type

SEES b2rust_types
    
CONCRETE_VARIABLES
    cv 
    
INVARIANT  cv : rust_i8 //ugly but i want to fit the full mch on the screen
    
INITIALISATION cv := 10
    
OPERATIONS
    
    res <-- op(tab,index,cc) = 
    PRE
        // Type operation parameters
        res : rust_i32 & 
        index : rust_u8 &
        tab : rust_u8 --> rust_i32 &
        cc : rust_i32 &
        
        // You don't have to type cv even throught if you use it in your
        // operation body, because cv is not a parameter
        
        //You can still have other conditions among the preconditions
        tab(0) > cc
    THEN
        //whatever postcondition you want, even 'skip'
        
        // You don't have to type cv even if you use it in your
        // operation body, because cv is not a parameter
        res := tab(index) + cc + cv
    END;
  
    decr = 
    BEGIN
        skip
    END
         
END
