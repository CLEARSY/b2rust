#!/bin/bash

# Generates every possible BXML file is the tests directories, with some exceptions.
# $1: the path to the Atelier B bbin directory which should contain a BXML executable.
# $2: the path to the test directory.
# $3: the path to Atelier B’s ressource file.

bbin=$1
test=$2
ress=$3

bxml=$bbin/bxml

# Files to delete after generation (can be useful for error checking).



exceptions="b2rust_types.mch"

if [ ! -f $bxml ]
then
   echo "The path to the BXML executable is bad."
   exit
fi

for dir in comparison errors main base_module c4b Industrial; do
    for subdir in $test/$dir/*; do
	if [ -d $subdir ]
	then
	    base=$(basename $subdir)
	    # for file in $base.mch ${base}_i.imp; do
	    for file in $subdir/*.mch $subdir/*.imp $subdir/*.ref; do
		    if [ -e $file ]
		    then
			if [ $(basename $file) = $exceptions ]
			then
			    continue
			fi
			command="$bxml -a -r $ress -i 4 -I $subdir -O $subdir $file"
			LD_LIBRARY_PATH=$bbin
			return=$($command)
			error=$?
			if [ $error -ne 0 ]
			then
			    echo "-- This command failed:"
			    echo LD_LIBRARY_PATH=$bbin $command
			    echo "-- The error code is:"
			    echo $error
			    echo "-- Its output is:"
			    echo $return
			    echo "-- Goodbye."
			    exit
			fi
		fi
	 done
	fi
    done
done



