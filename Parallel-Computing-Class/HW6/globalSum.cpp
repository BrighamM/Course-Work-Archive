#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <algorithm>

#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv){

    int myRank; 
    int worldSize;
    int myData = -99; 
    int receivedData = -99;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &myRank); 
    MPI_Comm_size(MCW, &worldSize);
    double startTime, endTime;

    myData = myRank;
    if(myRank == 0){
        cout << "Here we give some information. "<< endl;
        cout << "For this program we are going to perform Global sums. "<< endl;
        cout << "For ease and reference every processor is going to  "<< endl;
        cout << "have a chunk of data that is equal to it's rank. "<< endl;
        cout << "We are then going to sum all the values on every processor "<< endl;
        cout << "to attain some meaningful global sum. "<< endl;
        cout << "For four processors our sum will be 6. (3+2+1+0)"<< endl;
        cout << "For 8 processors our sum will be 28. (7+6+5+4+3+2+1+0)"<< endl;
        cout << "etc... "<< endl;
        cout << ""<< endl;        
        startTime = MPI_Wtime();
    }

    int logCube = log2(worldSize);

    int bitToCompareWith = 0; // This is the bit that is going to be compared with.
    int dest = 0;
    for(int i = 1; i <= logCube; i++){
        bitToCompareWith = pow(2,i - 1);
        dest = myRank^bitToCompareWith;
        MPI_Send(&myData,1,MPI_INT,dest,0,MCW);
        MPI_Recv(&receivedData,1,MPI_INT,dest,0,MCW,MPI_STATUS_IGNORE);
        myData += receivedData;
        MPI_Barrier(MCW);
        
    }

    if(myRank == 0){
        endTime = MPI_Wtime();
        cout << "Here we show the global sum for proc 0: " << myData << endl;
        cout << "The time for this run was: " << endTime - startTime << " seconds. We used " << worldSize << " processors." << endl;
        cout << "Now we run the program again, but this time we insert a 1 second wait time after every log level." << endl;
        cout << endl;
    }

    myData = myRank;
    if(myRank == 0){
        cout << "Starting the program with a 1 second timing interval at every log level. "<< endl;        
        startTime = MPI_Wtime();
    }

    logCube = log2(worldSize);

    bitToCompareWith = 0; // This is the bit that is going to be compared with.
    dest = 0;
    for(int i = 1; i <= logCube; i++){
        bitToCompareWith = pow(2,i - 1);
        dest = myRank^bitToCompareWith;
        MPI_Send(&myData,1,MPI_INT,dest,0,MCW);
        MPI_Recv(&receivedData,1,MPI_INT,dest,0,MCW,MPI_STATUS_IGNORE);
        myData += receivedData;
        if(myRank == 0){
            sleep(1);
        }
        MPI_Barrier(MCW);
    }

    if(myRank == 0){
        endTime = MPI_Wtime();
        cout << "Here we show the global sum for proc 0: " << myData << endl;
        cout << "The time for this run was: " << endTime - startTime << " seconds. We used " << worldSize << " processors." << endl;
        cout << "Now we run the program again, but this time we insert a 2 second wait time after every log level." << endl;
        cout << endl;
    }

    myData = myRank;
    if(myRank == 0){
        cout << "Starting the program with a 2 second timing interval at every log level. "<< endl;     
        startTime = MPI_Wtime();
    }

    logCube = log2(worldSize);

    bitToCompareWith = 0; // This is the bit that is going to be compared with.
    dest = 0;
    for(int i = 1; i <= logCube; i++){
        bitToCompareWith = pow(2,i - 1);
        dest = myRank^bitToCompareWith;
        MPI_Send(&myData,1,MPI_INT,dest,0,MCW);
        MPI_Recv(&receivedData,1,MPI_INT,dest,0,MCW,MPI_STATUS_IGNORE);
        myData += receivedData;
        if(myRank == 0){
            sleep(2);
        }
        MPI_Barrier(MCW);
    }

    if(myRank == 0){
        endTime = MPI_Wtime();
        cout << "Here we show the global sum for proc 0: " << myData << endl;
        cout << "The time for this run was: " << endTime - startTime << " seconds. We used " << worldSize << " processors." << endl;
        cout << "Now we run the program again, but this time we insert a 4 second wait time after every log level." << endl;
        cout << endl;
    }

    myData = myRank;
    if(myRank == 0){
        cout << "Starting the program with a 4 second timing interval at every log level. "<< endl;  
        startTime = MPI_Wtime();
    }

    logCube = log2(worldSize);

    bitToCompareWith = 0; // This is the bit that is going to be compared with.
    dest = 0;
    for(int i = 1; i <= logCube; i++){
        bitToCompareWith = pow(2,i - 1);
        dest = myRank^bitToCompareWith;
        MPI_Send(&myData,1,MPI_INT,dest,0,MCW);
        MPI_Recv(&receivedData,1,MPI_INT,dest,0,MCW,MPI_STATUS_IGNORE);
        myData += receivedData;
        if(myRank == 0){
            sleep(4);
        }
        MPI_Barrier(MCW);
    }

    if(myRank == 0){
        endTime = MPI_Wtime();
        cout << "Here we show the global sum for proc 0: " << myData << endl;
        cout << "The time for this run was: " << endTime - startTime << " seconds. We used " << worldSize << " processors." << endl;
        cout << "We are done. We have shown the effect of how fast a global operation can be under different " << endl;
        cout << "timings with a given number of processors." << endl;
    }

    MPI_Finalize();

    return 0;
}