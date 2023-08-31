MACHINE
	ordre_decl

SEES
	b2rust_types

SETS
	ss_import1
;	ss_import2
;	en_import1 = {elt_import1}
;	en_import2 = {elt_import2}

CONCRETE_CONSTANTS
	cc_import1
,	cc_import2
,	it_import1
,	it_import2

PROPERTIES
	cc_import1 : rust_i32
&	cc_import2 : rust_i32	
&	it_import2 = 2..100
&	it_import1 = 1..100

CONCRETE_VARIABLES
	vv_import2,
	vv_import1

INVARIANT
	vv_import2 : rust_i32
&	vv_import1 : rust_i32

INITIALISATION
	vv_import2 := 2
||	vv_import1 := 1

OPERATIONS
	op_extend2 = skip;
	op_promotes2 = skip;
	op_extend1 = skip;
	op_promotes1 = skip;

	op3 = skip;
	op2 = skip;
	op1 = skip
END
