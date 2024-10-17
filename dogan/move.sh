#!/bin/bash

for file in src/*; do
	if[[ -f "$file" ]]; then
		file_name=$(basename "$file" .cpp)
		echo "Moving $file to src/$file_name/"
		mkdir -p "src/$folder_name"
		mv "src/$file_name.cpp" "src/$file_name/"
		mv "include/$file.h" "src/$file_name/"
	fi
done
