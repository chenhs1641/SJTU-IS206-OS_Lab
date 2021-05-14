case $# in
	1)
	path=./
	pattern=$1
	;;
	2)
	path=$1
	pattern=$2
	;;
	*)
	echo "Parameter number wrong!"
	exit
	;;
esac

find $path -name "*.[ch]" | xargs grep -Hn $pattern
