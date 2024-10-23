#!/bin/bash

# Check if the user provided a directory
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory> [<directory> ...]"
    exit 1
fi

# Directory to format
DIRS=$@

ignore_conditions=""

while read -r line; do
    ignore_conditions+="! -name $line "
done < ".clang-format-ignore"

echo " IT IS $ignore_conditions"

# Find and format .h, .tpp and .cpp files
find $DIRS -type f \( -name "*.h" -o -name "*.tpp" -o -name "*.cpp" \) $ignore_conditions -exec clang-format -i {} +

echo "Formatting completed for all .h, .tpp and .cpp files"