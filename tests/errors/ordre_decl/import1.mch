MACHINE
	import1
SEES
	b2rust_types

SETS
	ss_import1
;	en_import1 = {elt_import1}

CONCRETE_CONSTANTS
	cc_import1
,	it_import1

PROPERTIES
	cc_import1 : rust_i32
&	it_import1 = 1..100


CONCRETE_VARIABLES
	vv_import1

INVARIANT
	vv_import1 : rust_i32

INITIALISATION
	vv_import1 := 1

OPERATIONS
	op_promotes1 = skip

END
