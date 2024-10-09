#!/bin/bash

# Check if an argument is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <argument>"
  exit 1
fi

touch src/$1.cc
touch include/$1.hh

# Use the argument
echo "The folloing files were created: "
echo "src/$1.cc"
echo "include/$1.hh"