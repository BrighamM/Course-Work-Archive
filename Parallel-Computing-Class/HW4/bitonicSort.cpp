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

void compareHi(int bitToCompareWith, int myRank, int &myPiece){
    int dest = myRank^bitToCompareWith; // exclusive or to obtain dest
    bool IamZero = !((myRank&bitToCompareWith) == bitToCompareWith);
    int receivedData;
    MPI_Send(&myPiece,1,MPI_INT,dest,0,MCW);
    MPI_Recv(&receivedData,1,MPI_INT,dest,0,MCW,MPI_STATUS_IGNORE);

    if(IamZero && (myPiece > receivedData)){
        myPiece = receivedData;
    }
    if((!IamZero) && (myPiece < receivedData)){
        myPiece = receivedData;
    }
}

void compareLo(int bitToCompareWith, int myRank, int &myPiece){
    int dest = myRank^bitToCompareWith; // exclusive or to obtain dest
    bool IamZero = !((myRank&bitToCompareWith) == bitToCompareWith);
    int receivedData;
    MPI_Send(&myPiece,1,MPI_INT,dest,0,MCW);
    MPI_Recv(&receivedData,1,MPI_INT,dest,0,MCW,MPI_STATUS_IGNORE);

    if(IamZero && (myPiece < receivedData)){
        myPiece = receivedData;
    }
    if((!IamZero) && (myPiece > receivedData)){
        myPiece = receivedData;
    }
}

int main(int argc, char **argv){

    int myRank; 
    int worldSize;
    int *myPiece = (int*)malloc(sizeof(int));
    srand((unsigned)time(0));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &myRank); 
    MPI_Comm_size(MCW, &worldSize); 

    // MPI_Send(&rank,1,MPI_INT,(rank+1)%size,0,MCW);
    // MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);

    // First lets create a vector of random ints.
    int *rand_nums = (int*)malloc(sizeof(int) * worldSize);
    int *completed_Array = (int*)malloc(sizeof(int) * worldSize);

    if(myRank == 0){
        cout << "Here we show the preiminary unsorted array." << endl;
        for(int i = 0; i < worldSize; i++){
            rand_nums[i] = rand()%1000;
            cout << rand_nums[i] << endl;
        }
    }

    MPI_Scatter(
        rand_nums,
        1,
        MPI_INT,
        myPiece,
        1,
        MPI_INT,
        0,
        MCW
    );
    
    MPI_Barrier(MCW); // Every processor needs to be here at the same time.

    int logCube = log2(worldSize); // This is log(number of processors)
    int bitToCompareWith = 0; // This is the bit that is going to be compared with.
    for(int i = 1; i <= logCube; i++){
        bitToCompareWith = pow(2,i - 1);
        if(!(((int)((myRank)/(pow(2,i))))%2)){ // THIS WAS THE HARDEST LINE IN THE CODE TO THINK UP!
            compareHi(bitToCompareWith, myRank, *myPiece); // The zero bit keeps the larger data.
        }
        else {
            compareLo(bitToCompareWith, myRank, *myPiece); // The zero bit keeps the smaller data.
        }
        MPI_Barrier(MCW);
        for(int j = i-1; j >= 1; j--){
            bitToCompareWith = pow(2,j - 1);
            if(!(((int)((myRank)/(pow(2,i))))%2)){
                compareHi(bitToCompareWith, myRank, *myPiece); // The zero bit keeps the larger data.
            }
            else {
                compareLo(bitToCompareWith, myRank, *myPiece); // The zero bit keeps the smaller data.
            }
            MPI_Barrier(MCW);
        }
    }

    MPI_Gather(
        myPiece, 
        1, 
        MPI_INT, 
        completed_Array, 
        1, 
        MPI_INT, 
        0,
        MCW
    );

    if(myRank == 0){
        cout << "The SORTED array for every processoror is:" << endl;
        for (int i = 0; i < worldSize; i++){
            cout << "VALUE: " << completed_Array[i] << endl;
        }
    }

    MPI_Finalize();

    return 0;
}