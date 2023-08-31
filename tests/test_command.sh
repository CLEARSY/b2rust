#!/bin/bash

# Just executes b2rust on the files provided by one test.

# $1 is the path to the binary.
# $2 is the tests directory.
# $3 is the category of the test.
# $4 is the name of the test.

b2rust=$1
tests=$2
category=$3
test=$4

echo "-a $tests/$category/$test/$test.bxml -i $tests/$category/$test/${test}_i.bxml"
exec $b2rust -a $tests/$category/$test/$test.bxml -i $tests/$category/$test/${test}_i.bxml
