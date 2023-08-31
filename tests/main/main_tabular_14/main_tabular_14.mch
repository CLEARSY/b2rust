/* typage d'un par d'operation par un tableau dont le codomaine
   est une C.A. incluse dans un set */

MACHINE
	main_tabular_14

SEES
    b2rust_types
    
SETS
	SURTYPE = {toto,tata,titi}
	
OPERATIONS
	oper1(x1, x2) =
	PRE
		x1 : (0..10) * (0..1) --> SURTYPE &
		x2 : (0..1) --> SURTYPE
	THEN
		skip
	END
END
	
