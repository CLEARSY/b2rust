/* concrete_constant_01
 * Author: 
 * Creation date: 21/03/2023
 */
MACHINE
    concrete_constant_01

ABSTRACT_CONSTANTS
    size_v, is_the_machine_on, annual_growth
    
CONCRETE_CONSTANTS
    employees
    
PROPERTIES
    size_v : INT &
    is_the_machine_on : BOOL &
    annual_growth : INT &
    employees : NAT
    
END