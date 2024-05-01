#!/usr/bin/env sh


for file in src/*
do
	# awk 'BEGIN{RS="^$";ORS="";getline;gsub("\r","");print>ARGV[1]}' $file
	sed -i  -e's/[[:space:]]*$//' "$file"
	echo "$file"
done

