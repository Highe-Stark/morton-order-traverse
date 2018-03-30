#!/bin/bash
prog="./morton_traverse ";
for file in ./src/res/* ; do
	$prog -f $file
done
