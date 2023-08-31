#!/bin/bash

# Given a directory containing the components as well as an entry component under the BXML shape, verifies that b2rust, when applied to the input, fails with an error code given in a file (the file contains nothing but an integer).
# Note that the calling of b2rust might generate some files. We don’t care.

# $1 is the execuable of b2rust.
# $2 is the directory containing the modules.
# $3 is the name of the module.
# $4 is the error file.

# $2 is the abstract machine.
# $3 is the implementation.

executable=$1
dir=$2
module=$3

am=$2
imp=$3
ef=$4

command="$executable -I $dir $module -O $dir"

echo -e "[error test] Proceeding test... Info: the command which is tested is \033[1m$command\033[0m. "

code=$(cat $ef)
error=$($command 2> /dev/null)
ec=$?

# Verifying 1)
find=$(find $dir -name "*.rs")
if [[ $find != "" ]]
then
    # Test fails.
    echo -ne '\033[1;31m ✖ Test failed.\033[0m b2rust likely produced some code. Output of'
    echo " \`find $dir -name \"*.rs\"\`: "
    echo $find
    exit 1;
fi

# Verifying 2)
if [[ $ec -ne $code ]]
then
    # Test fails.
    echo -ne '\033[1;31m ✖ Test failed.\033[0m b2rust failed, but with the bad error code: `'
    echo -n $ec
    echo -n '`; we want the error code `'
    echo -n $code
    echo '`.'
    exit 1;    
fi

# There might be an output...
rm -f $dir/$module.rs

echo -e '\033[0;32m✓ Test passed.\033[0m'
