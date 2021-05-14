function mytree() {
	for file in `ls -a $1`
    do
        if [ -d $1"/"$file ]
        then
			if [[ $file != '.' && $file != '..' ]]
            then
                mytree $1"/"$file "\t"$2
            fi
        else
            echo -e $2$file
        fi
    done
}
mytree ./ ""
