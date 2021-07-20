echo "Setting up folder for project $1"
mkdir $1 
cd $1 
echo "Creating a set of starting files for the project."
touch "$1_first.txt"
touch "README.md"
touch "$1.cpp"
touch "$1.h"


echo "# $1

## Goals:

## Purpose:

## Timeline:

" >> README.md


