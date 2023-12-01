#!/bin/bash
file_unix=$(echo $1 | sed 's:\\:/:g' | sed 's:C:/:c:')
output_unix=$(echo $2 | sed 's:\\:/:g' | sed 's:C:/:c/')
gcc -g $file_unix -o $output_unix