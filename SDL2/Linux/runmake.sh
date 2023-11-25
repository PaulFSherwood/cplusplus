#!/bin/bash

# Check if a file name is provided
if [ $# -eq 0 ]; then
    echo "No arguments provided. Please specify a .cpp file."
    exit 1
fi

# Prepare the .cpp file names as .o files
OBJS=""
for file in "$@"; do
    # let only the first file name be the OBJ_NAME
    if [[ -z $OBJ_NAME ]]; then
        OBJ_NAME="${file%.cpp}"
    fi

    if [[ $file == *.cpp ]]; then
        OBJS+="${file} "
    else
        echo "Warning: Ignoring non-cpp file $file"
    fi
done

# Update the Makefile
sed -i "s/^OBJS = .*/OBJS = $OBJS/" Makefile
sed -i "s/^OBJ_NAME = .*/OBJ_NAME = $OBJ_NAME/" Makefile

sleep 1
# Run make
make
