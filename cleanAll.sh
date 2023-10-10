#!/bin/bash

# Define the names of the executables to be removed
executables=("myprogram" "wordCounter" "invertedIndex")

# Loop through the array and remove each executable
for executable in "${executables[@]}"; do
    if [ -f "$executable" ]; then
        echo "Removing $executable..."
        rm "$executable"
        echo "$executable removed."
    else
        echo "$executable not found."
    fi
done
