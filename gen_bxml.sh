#!/bin/bash

# Generates every possible BXML file is the tests directories, with some exceptions.
# $1: the path to the Atelier B bbin directory which should contain a BXML executable.
# $2: the path to the machines directory.
# $3: the path to Atelier B’s ressource file.

bbin=$1
dir=$2
ress=$3

bxml=$bbin/bxml

# Files to delete after generation (can be useful for error checking).
exceptions="b2rust_types.mch"

if [ ! -f $bxml ]
then
   echo "The path to the BXML executable is bad."
   exit
fi


for file in $dir/*.mch $dir/*.imp $dir/*.ref; do
    if [ -e $file ]
    then
	if [ $(basename $file) = $exceptions ]
	then
	    continue
	fi
	command="$bxml -a -r $ress -i 4 -I $dir -O $dir $file"
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


