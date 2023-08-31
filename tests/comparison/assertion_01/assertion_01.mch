/* assertion_01
 * Author: 
 * Creation date: 13/04/2023
 */
MACHINE
    assertion_01
    
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
    dummy_inversion = BEGIN
        var1, var2 := var2, var1
    END

END
