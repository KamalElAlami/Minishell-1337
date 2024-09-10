#!/bin/bash

# Function to check for memory leaks
echo "program name >> "
read program
check_leaks() {
    leaks $program
}
cleanup() {
    echo "Stopping leak checks."
    exit 0
}
trap cleanup SIGINT SIGTERM
c=0
while true; do
    check_leaks
    sleep 3
    echo "======= $c ========"
    echo "                    "
    ((c++))
done