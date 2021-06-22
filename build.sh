#!/bin/bash

if [ -d bin -a -d obj ]; then
	rm -r bin obj
	echo "dilete obj and bin directory"
fi

# make directory for result of 'make'
mkdir bin obj
echo "make new bin obj directory for the output of result"

# output object and binary file of server/client
echo "now building server/client"
make

if [ -f bin/server ]; then
	echo "Success Server!"
else
	echo "Failure Server!"
fi
if [ -f bin/client ]; then
	echo "Success Client!"
else
	echo "Failure Client!"
fi
