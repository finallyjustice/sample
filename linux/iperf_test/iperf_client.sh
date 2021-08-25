#!/bin/bash

date > log.txt

while true; do
    date >> log.txt
    iperf -c 10.0.0.1 >> log.txt
done
