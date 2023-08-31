#!/bin/bash

# Executes the given b2rust command and verifies the output of the command.
# Helps to verify b2rust calling parameters errors.

# $1 is the path to b2rust.
# $2 is the file containing the command to execute.
# $3 is the error file.

executable=$1
command=$2
ef=$3


to_execute="$executable $(cat $command)"

echo -e "[call_code test] Executing command \`\033[1m$to_execute\033[0m\`..."

code=$(cat $ef)
$($to_execute > /dev/null 2>&1)
ec=$?


if [[ $ec -ne  $code ]]
then
    # Test fails.
    echo -ne '\033[1;31m ✖ Test failed.\033[0m. Expecting error code `'
    echo -n $code
    echo -n '`; got error code `'
    echo -n $ec
    echo '`.'
    exit 1;
fi

echo -e '\033[0;32m✓ Test passed.\033[0m'
