#!/bin/bash

processus=`ps | grep "$1.filler" | grep -v 'ruby' | grep -v 'grep' | cut -d ' ' -f 1`
while :
do 
	sleep 1
	clear
	leaks $processus
done
#leaks $processus
