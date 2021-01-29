#!/bin/bash
shopt -s xpg_echo

touch results.txt
total_pkts=$(cat /dev/stdin)
# For each line - remove spaces, extra commas and ignore comments
while read -r line
do
	line=$(echo "${line}" | sed 's/ //g' | awk -F# '{print $1}')
	line=$(echo "${line}" | sed -E 's/,+/,/g')
	if [[ "${line::1}" == ',' ]]; then	#If line starts with commea
		line=$(echo "$line" | sed 's/,//')
	fi
	if [[ "$line" != "" ]]; then
		echo "$total_pkts" > curr_pkts.txt
		IFS=',' read -r -a rule_array <<< "$line"
		for rule in "${rule_array[@]}"
		do
			./firewall.exe "$rule" < curr_pkts.txt > temp_pkts.txt
			cat temp_pkts.txt > curr_pkts.txt
		done
		cat curr_pkts.txt >> results.txt
	fi
done<$1		#Read rules file
cat results.txt | sort -u | sed 's/ //g'

rm curr_pkts.txt results.txt temp_pkts.txt
