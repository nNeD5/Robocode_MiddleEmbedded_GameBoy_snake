#!/usr/bin/env sh


for file in ./*
do
	awk 'BEGIN{RS="^$";ORS="";getline;gsub("\r","");print>ARGV[1]}' $file
	echo "$file"
done

