#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h> 
#include <vector>
#include <ctime>    
#include <cstdlib>  
#include <time.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

using namespace std;

const int squareSize = 16;

int getLiveNeighbors(bool image_array[squareSize+2][squareSize+2], int row, int col){

    int rollingLiveCount = 0;

    // TOP LEFT
    if(image_array[row-1][col-1]){
        rollingLiveCount++;
    }
    // TOP RIGHT
    if(image_array[row-1][col+1]){
        rollingLiveCount++;
    } 
    // BOTTOM LEFT
    if(image_array[row+1][col-1]){
        rollingLiveCount++;
    }
    // BOTTOM RIGHT
    if(image_array[row+1][col+1]){
        rollingLiveCount++;
    }
    // TOP
    if(image_array[row-1][col]){
        rollingLiveCount++;
    }
    // BOTTOM
    if(image_array[row+1][col]){
        rollingLiveCount++;
    }
    // LEFT
    if(image_array[row][col-1]){
        rollingLiveCount++;
    }
    // RIGHT
    if(image_array[row][col+1]){
        rollingLiveCount++;
    }   


    return rollingLiveCount;
}


int main(int argc, char **argv){

    int myRank; 
    int worldSize;
    int chunkSize = squareSize/worldSize;
    srand((unsigned)time(0));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &myRank); 
    MPI_Comm_size(MCW, &worldSize); 

    bool IMG_ARRAY[squareSize + 2][squareSize + 2] = {0};
    bool tempArray[squareSize + 2][squareSize + 2] = {0};
    bool myUpperRowToSend[squareSize + 2] = {0};
    bool myUpperRowToRecv[squareSize + 2] = {0};
    bool myLowerRowToSend[squareSize + 2] = {0};
    bool myLowerRowToRecv[squareSize + 2] = {0};
    int myStartRowNumber = ( chunkSize * myRank ) + 1;
    int myEndRowNumber = ( chunkSize * myRank ) + 1 + chunkSize;


    if(myRank == 0){
        for(int i=1;i<squareSize+1;i++) {
            for(int j=1;j<squareSize+1;j++) {
                IMG_ARRAY[i][j] = (rand()%5) ? true : false; 
            }
        }
    }
    // Now rank 0 needs to send out the matrix to everybody else.
    MPI_Bcast(IMG_ARRAY, ((squareSize + 2)*(squareSize + 2)), MPI_INT, 0, MCW);
    MPI_Barrier(MCW);

    cout << "I hate this thing" << endl;


    int daysToRun = 1;

    int numNeighbors = 0;        
    for(int row = myStartRowNumber; row <= myEndRowNumber; row++) {
        for(int col = 1; col < squareSize + 1; col++) {
            numNeighbors = getLiveNeighbors(IMG_ARRAY, row, col);
            if(IMG_ARRAY[row][col] && numNeighbors == 0){
                tempArray[row][col] = false;
                continue;
            }
            if(IMG_ARRAY[row][col] && numNeighbors == 1){
                tempArray[row][col] = false;
                continue;
            }
            if(IMG_ARRAY[row][col] && numNeighbors == 2){
                tempArray[row][col] = true;
                continue;
            }
            if(IMG_ARRAY[row][col] && numNeighbors == 3){
                tempArray[row][col] = true;
                continue;
            }
            if(IMG_ARRAY[row][col] && numNeighbors >= 4){
                tempArray[row][col] = false;
                continue;
            }
            if(!IMG_ARRAY[row][col] && numNeighbors == 3){
                tempArray[row][col] = true;
                continue;
            }
        }
    }

    // Set up myStartRowNumber and myEndRowNumber.

    for(int i = 0; i < squareSize + 2; i++){
        myUpperRowToSend[i] = tempArray[myStartRowNumber][i];
    }
    for(int i = 0; i < squareSize + 2; i++){
        myLowerRowToSend[i] = tempArray[myEndRowNumber][i];
    }


    // cout << "Prepare to send your upper row. myRank: " << worldSize << endl;
    // MPI_Barrier(MCW);
    // if(myRank - 1 >= 0) {
    //     MPI_Send(&myUpperRowToSend,squareSize + 2,MPI_INT,myRank - 1,0,MCW);
    // }

    // cout << "Prepare to Recv your lower row." << endl;
    // MPI_Barrier(MCW);
    // if(myRank != worldSize - 1) {
    //     MPI_Recv(&myLowerRowToRecv,squareSize + 2,MPI_INT,myRank + 1,0,MCW,MPI_STATUS_IGNORE); 
    // }

    // cout << "Prepare to send your lower row" << endl;
    // MPI_Barrier(MCW);
    // if(myRank != worldSize - 1) {
    //     MPI_Send(&myLowerRowToSend,squareSize + 2,MPI_INT,myRank + 1,0,MCW);
    // }

    // cout << "Prepare to recv your upper row" << endl;
    // if(myRank != 0){
    //     MPI_Recv(&myUpperRowToRecv,squareSize + 2,MPI_INT,myRank - 1,0,MCW,MPI_STATUS_IGNORE);
    // }
    // MPI_Barrier(MCW);

    for(int i = 0; i < squareSize + 2; i++){
        tempArray[myStartRowNumber - 1][i] = myUpperRowToRecv[i];
    }
    for(int i = 0; i < squareSize + 2; i++){
        tempArray[myEndRowNumber + 1][i] = myLowerRowToRecv[i];
    }

    for(int row=1;row < squareSize+1;row++) {
        for(int col=1;col < squareSize+1;col++) {
            IMG_ARRAY[row][col] = tempArray[row][col];
            tempArray[row][col] = 0;
        }
    }        
    
    MPI_Finalize();
    return 0;
}