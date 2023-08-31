#!/bin/bash

# Given a directory whose basename is `$dir`, a b2rust executable, executes this workflow:
# 1) Run b2rust on the given directory, supposing the input component is the basename of the dir;
# 2) Compile the generated Rust program as an external library;
# 3) Compile the `main.rs` file of `$dir` with a link to the generated library;
# 4) Executes the generated binary.
# If these steps succeed (i.e. their return code is `0` everytime), the test succeeds. Otherwise, it fails.

b2rust=$1
dir=$2

echo -e "[error test] Proceeding test..."


exitme() {
    temp=$(mktemp)
    mv $dir/main.rs $temp
    rm -f $lib $main $dir/*.rs
    mv $temp $dir/main.rs
    exit $1
}


# 1)
base=$(basename $dir)
file=$dir/$base.rs

command="$b2rust -O $dir -I $dir $base"
echo -e "Executing command \`$command\`"...

return=$($command 2>&1)

if [ $? -ne 0 ]
then
    echo -e '\033[1;31m ✖ Test failed\033[0m while running `b2rust` on the given BXML files! The output of b2rust is:'
    echo -e $return
    exitme 1;
fi




# 2)
lib=$dir/lib$base.rlib
command="rustc --crate-type=lib $file -o $lib"

echo -e "Executing command \`$command\`..."

return=$($command 2>&1)

if [ $? -ne 0 ]
then
    error=$?
    echo -e '\033[1;31m ✖ Test failed\033[0m while trying to compile the `b2rust` generated program!';
    if [ $error -eq 127 ]
    then
	echo 'Error code is 127; note that the `rustc` tool, used to compile in Rust, needs to be in your `$PATH`! However, the output is:'
    elif [ $error -eq 1 ]
    then
	echo "Error code is 1; the Rust compilation failed, sorry. The output is:"
    else
	echo "Unknown error. The output is:"
    fi
    echo -e $return
    exitme 1;

fi


# 3)
main=$dir/main
command="rustc --extern $base=$dir/lib$base.rlib $dir/main.rs -o $main"

echo -e "Executing command \`$command\`..."

return=$($command 2>&1)

if [ $? -ne 0 ]
then
    error=$?
    echo -e '\033[1;31m ✖ Test failed\033[0m while trying to compile the `main.rs` file while linking the generated library!';
    if [ $error -eq 1 ]
    then
	echo "Error code is 1; the Rust compilation failed. Is the provided `main.rs` program correct? The output is:"
    else
	echo "Unknown error. The output is:"
    fi
    echo -e $return
    exitme 1;
fi


# 4)
command=$main

echo -e "Executing binary \`$command\`"...

return=$($command 2>&1)

if [ $? -ne 0 ]
then
    echo -e '\033[1;31m ✖ Test failed\033[0m while executing the generated `main`! The output is:';
    echo -e $return
    exitme 1;
fi

exitme 0;
