timeout=5
log="log.file"
line=1
tot=0

waitProcess()
{
    PID=$!
    while [[ "$i" -lt "$timeout" ]]
    do
        sleep 0.1
        if ! [ -e /proc/$PID ];
        then
            echo "Test done in about $((i * 100)) ms"
            break
        fi
	$i=$(($i + 1))
    done
    if [ -e /proc/$PID ];
    then
        echo "Kill process"
        kill $PID
    fi
    wait $PID
}

if [ $(echo $#) -eq 0 ]
    then
    echo "Usage : ./test.sh fichierTest [TIMEOUT]"
    exit
    fi

if [ $# -gt 1 ]
    then
    timeout=$2
fi

rm $log 2> /dev/null
touch $log

while read cmd
do
    if [[ "$cmd" != "waitProcess" ]]
	then
	echo "Processing test line: $line"
	line=$(($line + 1))
	fi
    if [ "${cmd:0:1}" != '#' ]
	then
	eval $cmd
	fi
done < $1
