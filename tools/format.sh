#!/bin/bash

# Check if the user provided a directory
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory> [<directory> ...]"
    exit 1
fi

# Directory to format
DIRS=$@

# Find and format .h, .tpp and .cpp files
find $DIRS -type f \( -name "*.h" -o -name "*.tpp" -o -name "*.cpp" \) -exec clang-format -i {} +

echo "Formatting completed for all .h, .tpp and .cpp files"