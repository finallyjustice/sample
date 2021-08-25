#!/bin/bash

date > log.txt

while true; do
    date >> log.txt
    iperf -s
done
