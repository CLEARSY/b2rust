#!/bin/bash

# This file is read during the `cmake` compilation.
# Each directory among ($3, $4, $5) aggregates a category of tests. It is the purpose of this script to generate in the file $2 a line to indicate CMake which script to call and with which parameters for every test which exists.
# In each directory, there’s a `test.sh` script which takes unspecified parameters and which performs a certain test (the work this script do depends on the category of the test).
# $3 is the `comparison` directory; it executes b2rust on the given BXML files and checks if the output matches a given Rust code file.
# $4 is the `errors` directory; it executes b2rust on the given BXML files and checks that b2rust refuses to generate code for these files.
# $5 is the `main` directory; it executes b2rust on the given BXML files, compile the result, compile a given `main.rs` file, and executes the generated binary.


# $1: the executable of the program.
# $2 is the file where the line is generated.
# $3 is the `comparison` directory.
# $4: the `errors` directory.
# $5: the `main` directory.
# $6: the `call_code` directory.

executable=$1
tests_file=$2

comparison=$3
errors=$4
main=$5
call_code=$6
base_mod=$7
c4b=$8
industrial=$9

echo -n "-- Generatig the tests list... "
# TODO: make the verifications (for example that we have the rights...)
rm $tests_file

tests_number=0

# Generation of the comparison tests.
for dir in $comparison/*; do
    if [ -d $dir ]
    then
	base=$(basename $dir)
	echo "add_test(\"comparison: $base\" $comparison/test.sh $base $executable $dir $base $dir/r_$base.rs )" >> $tests_file
	tests_number=$(($tests_number+1))
    fi
done


# Generation of the tests for the errors.
for dir in $errors/*; do
    if [ -d $dir ]
    then
	base=$(basename $dir)
	echo "add_test(\"error: $base\" $errors/test.sh $executable $errors/$base/ $base $errors/$base/error )" >> $tests_file
	tests_number=$(($tests_number+1))
    fi
done


# Generation of the tests for the main tests.
for dir in $main/*; do
    if [ -d $dir ]
    then
	base=$(basename $dir)
	echo "add_test(\"main: $base\" $main/test.sh $executable $main/$base )" >> $tests_file
	tests_number=$(($tests_number+1))
    fi
done


# Generation of the tests for the `call_code`.
for dir in $call_code/*; do
    if [ -d $dir ]
    then
	base=$(basename $dir)
	echo "add_test(\"call_code: $base\" $call_code/test.sh $executable $call_code/$base/command $call_code/$base/error )" >> $tests_file
	tests_number=$(($tests_number+1))
    fi
done

for dir in $base_mod/*; do
    if [ -d $dir ]
    then
	base=$(basename $dir)
	echo "add_test(\"base_module: $base\" $base_mod/test.sh $executable $base_mod/$base )" >> $tests_file
	tests_number=$(($tests_number+1))
    fi
done

for dir in $c4b/*; do
    if [ -d $dir ]
    then
	base=$(basename $dir)
	echo "add_test(\"c4b_test: $base\" $c4b/test.sh $executable $c4b/$base )" >> $tests_file
	tests_number=$(($tests_number+1))
    fi
done

for dir in $industrial/*; do
    if [ -d $dir ]
    then
	base=$(basename $dir)
	echo "add_test(\"industrial_test: $base\" $industrial/test.sh $executable $industrial/$base )" >> $tests_file
	tests_number=$(($tests_number+1))
    fi
done

echo "$tests_number test generated."
