#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Invalid command number"
    exit 1
fi

# stampa la mappa
a=$1
let a=a-1
n=0
while [ $a -ge 0 ]
do
    b=$2
    let b=b-1
    while [ $b -ge 0 ]
    do
        echo -n -e $n "\t"
        let n=n+1
        let b=b-1
    done
    let a=a-1
    echo ""
done

# crea nodes.txt
a=0
cost=0
id=0
while [ $a -lt $1 ]
do
    b=0
    while [ $b -lt $2 ]
    do
        echo $id $cost $a $b
        let id=id+1
        let b=b+1
    done
    let a=a+1
done > nodes.txt


# crea links.txt
a=0
cost=1
id=0
while [ $a -lt $1 ]
do
    b=0
    while [ $b -lt $2 ]
    do
        if [ $a -gt 0 ]
        then
            let from=id-$1
            echo $from $id $cost
        fi
        if [ $b -gt 0 ]
        then
            let from=id-1
            echo $from $id $cost
        fi
        let id=id+1
        let b=b+1
    done
    let a=a+1
done > links.txt
