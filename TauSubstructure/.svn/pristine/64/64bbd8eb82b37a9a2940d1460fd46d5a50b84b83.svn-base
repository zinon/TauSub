#!/bin/sh

echo "Memory info:"
cat /proc/meminfo

echo "Memory stats:"
vmstat -s

export workplace=${PWD}

echo "RunAnalysis: workplace " $workplace

ls $workplace

export launch=RunGrid.C
export compile=Compile.C
export input=inputfiles.txt
# export input=misc/test.data.local.txt
#  export input=test.mc.local.txt.1

if [ ! -f $launch ]
then
    echo "RunAnalysis: File" $launch " not found!"
fi

if [ ! -f $compile ]
then
    echo "RunAnalysis: File" $compile " not found!"
fi

if [ ! -f $input ]
then
    echo "RunAnalysis: File" $input " not found!"
fi

echo;

echo "RunAnalysis: Input files ...";
cat $input;
wc $input;

echo;

echo "RunAnalysis: Compiling ..."

root.exe -b -q -l $compile

echo "RunAnalysis: Executing ..."

root -b -q -l ${launch}\(\"$input\"\)

echo "RunAnalysis: Done!"

