#!/bin/bash

declare -i files=0
declare -i dires=0

for f in $1/* 
do
	[`analyseFichier.sh $f` == "$f is a file"] && files= expr $files+1
	[`analyseFichier.sh $f` == "$f is a directory"] && dires= expr$dires+1
done
echo "files: $files"
echo "dirs: $dires" 

