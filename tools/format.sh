#!/bin/bash

# Check if the user provided a directory
if [ -z "$1" ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Directory to format
DIR=$1

# Find and format .h and .cpp files
find "$DIR" -type f \( -name "*.h" -o -name "*.tpp" -o -name "*.cpp" \) -exec clang-format -i {} +
find "$DIR" -type f -name "*.tpp" -exec clang-format -i {} +

echo "Formatting completed for all .h, .tpp and .cpp files in $DIR."