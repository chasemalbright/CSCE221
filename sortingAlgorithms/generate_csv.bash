#!/bin/bash


### This program prints statistics in CSV format.
### It is optional (you can do this manually if needed)
### Run under MacOS or WSL
###
### USAGE:
### Compile your program with:
### g++ -std=c++17 -o src/main src/main.cpp
###
### Run: bash generate_csv.bash > sorting_data.csv

bench() {
	local sort_arg="$1"
	local file_prefix="$2"

	echo "size,comparisons,duration(us)"
	echo -n "100,"
	./src/main ${sort_arg} "input-files/${file_prefix}100.dat"
	echo -n "1000,"
	./src/main ${sort_arg} "input-files/${file_prefix}1k.dat"
	echo -n "10000,"
	./src/main ${sort_arg} "input-files/${file_prefix}10k.dat"
}

bench_all() {
	local sort_arg="$1"
	local sort_name="$2"
	echo "${sort_name} [ORDERED]"
	bench ${sort_arg} ordered
	echo "${sort_name} [RANDOM]"
	bench ${sort_arg} rand
	echo "${sort_name} [REVERSE]"
	bench ${sort_arg} reverse
	echo "${sort_name} [RANDOM WITH DUPLICATES]"
	bench ${sort_arg} randdup
}

bench_all "-s" "SELECTION"
bench_all "-i" "INSERTION"
bench_all "-b" "BUBBLE"
