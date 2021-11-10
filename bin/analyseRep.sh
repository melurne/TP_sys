#!/bin/bash

for file in $1/* 
do
	analyseFichier.sh $file
done
