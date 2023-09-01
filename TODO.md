## SEES clause

SEES clause is not well translated yet, please refer to the reference manual of B language. 
For the moment; the SEES clause is translated as an IMPORTS clause.

## Type inference

Currently, atomic data must be typed using the CONSTANTS defined in the MACHINE `b2rust_types`.
It would be nice to have some heuristics that guess the "best" Rust type and lift this constraint.
