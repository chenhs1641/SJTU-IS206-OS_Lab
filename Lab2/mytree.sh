function mytree() {
    for file in `ls -a $1`
    do
        if [ -d $1"/"$file ]
        then
            if [[ $file != '.' && $file != '..' ]]
            then
                echo "$2$file"
                mytree $1"/"$file "    $2"
            fi
        else
            echo "$2$file"
        fi
    done
}
mytree ./ ""
