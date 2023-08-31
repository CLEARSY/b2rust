MACHINE
    Stack

ABSTRACT_VARIABLES
    Contents

SEES b2rust_types

INVARIANT
    Contents : seq ( rust_i8 ) &
    size ( Contents ) <= 10


INITIALISATION
    Contents := <>

OPERATIONS

    push ( value ) =
    PRE
        value : rust_i8 &
        size ( Contents ) < 10
    THEN
        Contents := value -> Contents
    END
    ;

    value <-- pop =
    PRE
    	value : rust_i8 &
        size ( Contents ) >= 1
    THEN
        value := Contents ( 1 ) ||
        Contents := tail ( Contents )
    END
END
