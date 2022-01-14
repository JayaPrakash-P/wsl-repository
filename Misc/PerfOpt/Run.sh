#!/bin/bash
#Pass process to run as arguments
for processName in "$@"
do
    echo "*******************************"
    echo "Running [$processName]...";
    echo "*******************************"
    echo -ne '\n' | ./$processName           #>> TestRun.log
    echo "*******************************"
    rm -rf $processName
done

#for processName in optgraph_updated_O1 optgraph_updated_O2 optgraph_updated_O3 optgraph_updated_Ofast optgraph_O1 optgraph_O2 optgraph_O3 optgraph_Ofast
#do
#    rm -rf $processName
#done
#
#g++ -std=c++11 -O1    optgraph_JP.cpp -o optgraph_updated_O1
#g++ -std=c++11 -O2    optgraph_JP.cpp -o optgraph_updated_O2
#g++ -std=c++11 -O3    optgraph_JP.cpp -o optgraph_updated_O3
#g++ -std=c++11 -Ofast optgraph_JP.cpp -o optgraph_updated_Ofast
#g++ -std=c++11 -O1    optgraph.cpp    -o optgraph_O1
#g++ -std=c++11 -O2    optgraph.cpp    -o optgraph_O2
#g++ -std=c++11 -O3    optgraph.cpp    -o optgraph_O3
#g++ -std=c++11 -Ofast optgraph.cpp    -o optgraph_Ofast
#g++ -std=c++11 optgraph_JP.cpp -o optgraph_updated
#g++ -std=c++11 optgraph.cpp -o optgraph
#
#rm -rf TestRun.log

#g++ -std=c++11        optgraph_V0.cpp -o optgraph_updated_V0
#g++ -std=c++11 -O1    optgraph_V0.cpp -o optgraph_updated_V0_O1
#g++ -std=c++11 -O2    optgraph_V0.cpp -o optgraph_updated_V0_O2
#g++ -std=c++11 -O3    optgraph_V0.cpp -o optgraph_updated_V0_O3
#g++ -std=c++11 -Ofast optgraph_V0.cpp -o optgraph_updated_V0_Ofast
#g++         optgraph_V1.cpp -o optgraph_updated_V1
#g++  -O1    optgraph_V1.cpp -o optgraph_updated_V1_O1
#g++  -O2    optgraph_V1.cpp -o optgraph_updated_V1_O2
#g++  -O3    optgraph_V1.cpp -o optgraph_updated_V1_O3
#g++  -Ofast optgraph_V1.cpp -o optgraph_updated_V1_Ofast

#for processName in optgraph_updated_O1 optgraph_updated_O2 optgraph_updated_O3 optgraph_updated_Ofast optgraph_O1 optgraph_O2 optgraph_O3 optgraph_Ofast
#for processName in optgraph_updated_V0 optgraph_updated_V0_O1 optgraph_updated_V0_O2 optgraph_updated_V0_O3 optgraph_updated_V0_Ofast optgraph_updated_V1 optgraph_updated_V1_O1 optgraph_updated_V1_O2 optgraph_updated_V1_O3 optgraph_updated_V1_Ofast
#for processName in optgraph_updated_V1 optgraph_updated_V1_O1 optgraph_updated_V1_O2 optgraph_updated_V1_O3 optgraph_updated_V1_Ofast
#for processName in optgraph_V1 optgraph_V0
#do
#    echo "\nRunning [$processName]..."        #>> TestRun.log
#    echo "-------------------------------  " #>> TestRun.log
#    for i in {1..10}
#    do
#        echo -ne '\n' | ./$processName           #>> TestRun.log
#    done
#    echo "-------------------------------  " #>> TestRun.log
#done
