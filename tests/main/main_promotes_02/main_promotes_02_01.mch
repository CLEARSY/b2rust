/* main_promotes_02_01
 * Author: cchen4
 * Creation date: 06/07/2023
 */
MACHINE
    main_promotes_02_01

SEES
	b2rust_types

OPERATIONS
    res <-- op_01 =
    PRE
        res : rust_i8
    THEN
    	res :: rust_i8
    END
    
END
