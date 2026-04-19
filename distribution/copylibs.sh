#!/bin/bash
mkdir -p ./dynlibs
deps=$(ldd $1 | awk '{ print $3 }')
for dep in $deps
do
if [ ${#dep} -gt 0 ]
then
cp "$dep" ./dynlibs
fi
done
