#!/usr/bin/bash
store=`date` #`date +'%d-%m-%Y'`
currentWorkingDirectory=`pwd`
cd ../
parentWorkingDirectory=`pwd`
cd "$currentWorkingDirectory"

currentDirectory="./*.o"
parentDirectory="../*.o"
DIRNAME="libnotify"

#remove any and all object files if they exists
#rm *.o ../*.o > log.log
#!/bin/bash

#0 will be false and 1 will be true
objectFileExistInCurrentDirectory=0
objectFileExistInParentDirectory=0

if [[ -f currentDirectory ]]; then
    ((objectFileExistInCurrentDirectory++))
fi

if [[ -f parentDirectory ]]; then
    ((objectFileExistInParentDirectory++))
fi


if [[ $objectFileExistInCurrentDirectory -eq 0 && $objectFileExistInParentDirectory -eq 0 ]]; then
#mean no object file found
echo "$store:No object files Detected in $currentWorkingDirectory and $parentWorkingDirectory" >> log.log
echo "All clean"

elif [[ $objectFileExistInCurrentDirectory -eq 1 ]]; then
echo "$store:Removing Object files from $currentWorkingDirectory" >> log.log
rm ./*.o 

elif [[ $objectFileExistInParentDirectory -eq 1 ]]; then
echo "$store:Removing Object files from $parentWorkingDirectory" >> log.log
rm ../*.o 

else

echo "$store:Unexpected bug " >> log.log
fi


# go into the root directory anc check if libnotify
#direcotory exists
#if [[ -d $DIRNAME ]]
#then
#echo "Dirctory exists"
#fi

#gcc timeDaemon.c -o timeDaemon
#sleep 3
#./timeDaemon