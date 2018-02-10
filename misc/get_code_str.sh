#!/bin/sh

if [ -z "$1" ]; then
	interpreter="/bin/bash"
else
	interpreter="$1"
fi
sleep 0.1
for i in {1..31}
do
	printf "%2i --> " $i
	code=$("$interpreter" <<< "ls -lR / &>/dev/null & killall -$i ls" 2>&1 | awk 'BEGIN {FS=":"} {print $3}' | sed 's/^ [0-9]* //g')
	if [ -z "$code" ]; then
		 printf \\n
	else
		echo "$code"
	fi
done
