MACHINE
	expression_1_mch
SETS
	EnsEnum = { ElemEnum1,  ElemEnum2 }
	
SEES
	b2rust_types
	
CONCRETE_CONSTANTS
	Cst1
	
PROPERTIES
	Cst1 : rust_i32
	
OPERATIONS
	p_out1,p_out2,p_out3,p_out4,p_out5<--opexp(p_in1,p_in2) = 
	PRE 
		p_in1 : rust_i32 & 
		p_in2 : BOOL &
		p_out1 : rust_i32 &
		p_out2 : rust_i32 &
		p_out3 : EnsEnum &
		p_out4 : BOOL &
		p_out5 : BOOL
	THEN 
		p_out1 := 0 ||
		p_out2 := 0 ||
		p_out3 := ElemEnum2 ||
		p_out4 := TRUE ||
		p_out5 := FALSE
	END
END
