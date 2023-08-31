/* local_type
 * Author: cchen4
 * Creation date: 21/08/2023
 */
MACHINE
    local_type
SEES
    b2rust_types
    
SETS
	SURTYPE = {toto,tata,titi}
	
OPERATIONS
	op(tab1, tab2) =
	PRE
		tab1 : (0..10) * (0..1) --> SURTYPE &
		tab2 : (0..1) --> SURTYPE
	THEN
		skip
	END
END
	