#!/bin/bash

MAX_RULES=6 	#Max number of rules in line is 4 we took extra care for special
				#cases (line begins or ends with comma)
results=""
tot_packets=$(cat /dev/stdin)
# For each line - remove spaces, extra commas and ignore comments
while read line
do
	curr_packets="$tot_packets"
	echo "$tot_packets" > curr_packets.txt
	line=$(echo "${line}" | sed 's/ //g' | awk -F# '{print $1}')
	line=$(echo "${line}" | sed -E 's/,+/,/g')
	for(( i=1; i<=$MAX_RULES; i++));do
		temp_rule=$(echo "${line}" | awk -F, -v num="$i" '{print $num}')
		if [[ "$temp_rule" != "" ]]; then
			# curr_packets=$(echo "$curr_packets" | ./firewall.exe "$temp_rule")
			
			echo "$temp_rule"
			./firewall.exe ""${temp_rule}"" < curr_packets.txt > curr_packets.txt
			echo ------------------------------------------
		fi
	done
	# echo "$curr_packets"
	# echo --------------------------------
	results+=$(echo $'\n')
	results+=$(cat curr_packets.txt)
done<$1		#Read rules file
results=$(echo "$results" | sort -u | sed 's/ //g')
echo "$results"
