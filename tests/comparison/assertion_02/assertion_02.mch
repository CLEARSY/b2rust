/* assertion_02
 * Author: 
 * Creation date: 13/04/2023
 */
MACHINE
    assertion_02

ABSTRACT_VARIABLES
    var1, var2, var3
    
INVARIANT
    var1 : NAT &
    var2 : NAT &
    var3 : NAT

INITIALISATION
    var1 := 0 ||
    var2 := 10 ||
    var3 := 3615
    
OPERATIONS
    zero = BEGIN
        var1, var2, var3 := 0, 0, 0
    END
    
END
