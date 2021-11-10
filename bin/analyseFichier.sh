#!/bin/bash

if ! test -z $2; then
	echo "Too many arguments passed, only processing first argument"
fi
if test -z $1; then
	echo "no argument were passed"
elif test -f $1; then
	echo "$1 is a file"
elif test -d $1; then
	echo "$1 is a directory"
else
	echo "$1 does not exist"
fi
