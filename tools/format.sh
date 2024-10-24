#!/bin/bash

# Check if the user provided a directory
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory> [<directory> ...]"
    exit 1
fi

# Directory to format
DIRS=$@

ignore_conditions=""

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"
cd ..

while read -r line; do
    echo "Ignoring $line"
    ignore_conditions+="! -name $line "
done < ".clang-format-ignore"

# Find and format .h, .tpp and .cpp files
find $DIRS -type f \( -name "*.h" -o -name "*.tpp" -o -name "*.cpp" \) $ignore_conditions -exec clang-format -i {} +

echo "Formatting completed for all .h, .tpp and .cpp files"