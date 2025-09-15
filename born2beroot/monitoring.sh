#!/bin/bash

monitoring_data=$(cat <<EOF
# Architecture: $(uname -a)
# CPU physical: $(lscpu | grep 'Socket(s):' | awk '{print $2}')
# vCPU: $(nproc)
# Memory Usage: $(free -m | awk 'NR==2{printf "%s/%sMB (%.2f%%)", $3,$2,$3*100/$2}')
# Disk Usage: $(df -h --total | awk 'END{printf "%s/%s (%s)", $3,$2,$5}')
# CPU load: $(mpstat | awk 'END{print 100 - $NF}')%
# Last boot: $(who -b | awk '{print $3, $4}')
# LVM use: $(if [ $(lsblk | grep -c lvm) -gt 0 ]; then echo "yes"; else echo "no"; fi)
# Connections TCP: $(ss -tn state established | wc -l) ESTABLISHED
# User log: $(who | wc -l)
# Network: IP $(hostname -I | awk '{print $1}') ($(ip -o link show | awk -F': ' '/link\/ether/{print $2}' | cut -d' ' -f1 | head -n1))
# Sudo: $(if [ -f /var/log/sudo.log ]; then wc -l < /var/log/sudo.log | awk '{print $1}'; else echo 0; fi) cmd
EOF
)

for tty in $(ps -ef | grep -e " tty" -e " pts/" | tr -s " " | cut -d " " -f 6 | sort -u); do
    if [ -w /dev/$tty ]; then
        echo "$monitoring_data" > /dev/$tty
    fi
done









