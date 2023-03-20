#!/bin/bash

process_file() {
    local file="$1"
    local new_name=$(echo "$file" | sed 's/\(.*\)/\L\1/' | sed 's/ /_/g' | sed 's/-/_/g' | sed 's/[()]//g')

    if [ "$file" != "$new_name" ]; then
        mv -v "$file" "$new_name"
    fi
}

export -f process_file

# Process directories
find . -type d -not -path '*/\.*' -exec bash -c 'process_file "$0"' {} \;

# Process files
find . -type f -not -path '*/\.*' -exec bash -c 'process_file "$0"' {} \;

