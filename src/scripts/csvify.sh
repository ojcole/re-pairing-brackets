if [ $# -lt 1 ]; then
    echo "Usage: ./csvify.sh [source_dir]"
    exit
fi

echo "Length,Width 1,Width 2,Width 3,Width 4"

regex="^[0-9]*(,[0-9]*)*$"
results=()

for folder in "$@"; do
    files=$(find $folder -type f)
    for file in $files; do
        next=0
        prev=""
        while IFS="" read -r p || [ -n "$p" ]; do
            if [[ $p =~ $regex ]]; then
                next=1
            elif [[ next -gt 0 ]]; then
                next=0
                result=$(echo $p | sed 's/[^0-9]*//g')
                line=$(printf '%s,%s\n' $result $prev)
                results+=($line)
            fi
            prev=$p
        done < $file
        unset IFS
    done
done

IFS=$'\n'
sorted=($(sort <<<"${results[*]}"))
unset IFS

for result in ${sorted[@]}; do
    echo $result
done
