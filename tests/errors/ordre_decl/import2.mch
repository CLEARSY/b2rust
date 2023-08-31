MACHINE
	import2

SEES
	b2rust_types
	
SETS
	ss_import2
;	en_import2 = {elt_import2}

CONCRETE_CONSTANTS
	cc_import2
,	it_import2

PROPERTIES
	cc_import2 : rust_i32
&	it_import2 = 2..100

CONCRETE_VARIABLES
	vv_import2

INVARIANT
	vv_import2 : rust_i32

INITIALISATION
	vv_import2 := 2

OPERATIONS
	op_promotes2 = skip

END
