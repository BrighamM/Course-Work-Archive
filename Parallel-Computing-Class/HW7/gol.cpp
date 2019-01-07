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

const int squareSize = 32;

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
    srand((unsigned)time(0));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &myRank); 
    MPI_Comm_size(MCW, &worldSize); 

    bool IMG_ARRAY[squareSize + 2][squareSize + 2] = {0};
    bool tempArray[squareSize + 2][squareSize + 2] = {0};

    for(int i=1;i<squareSize+1;i++) {
		for(int j=1;j<squareSize+1;j++) {
            IMG_ARRAY[i][j] = rand()%3; 
        }
    }

    // IMG_ARRAY[6][4] = 1;
    // IMG_ARRAY[6][5] = 1;
    // IMG_ARRAY[6][6] = 1;
    // IMG_ARRAY[5][6] = 1;
    // IMG_ARRAY[4][5] = 1;

    stringstream numericInput;    

    string fileName = "./ppmfiles/output";
    string fileNameNumber = numericInput.str();
    string fileNameTermination = ".ppm";
    string trueFileName = fileName + fileNameNumber + fileNameTermination;

    /**
     * 
     *       every organism that has 0 or 1 neighbors dies of lonelines.
        every organism that has 2 or 3 neighbors survives to the next day.
        every organism that has 4 or more neighbors dies of overcrowding.
        every cell that has exactly three neighbors gives birth to a new organism.
     * 
     */

    int daysToRun = 200;



    // for(int row=0;row < squareSize+2;row++) {
    //     for(int col=0;col < squareSize+2;col++) {
    //         cout << IMG_ARRAY[row][col] << " ";
    //     }
    //     cout << endl;
    // }

    for(int k = 0; k < daysToRun; k++){

        int numNeighbors;
        if(k == 30) {
            for(int index = 0; index < squareSize - 21; index += 20){
                IMG_ARRAY[6][4 + index] = 1;
                IMG_ARRAY[6][5 + index] = 1;
                IMG_ARRAY[6][6 + index] = 1;
                IMG_ARRAY[5][6 + index] = 1;
                IMG_ARRAY[4][5 + index] = 1;
            }

        }
        
        for(int row=1;row < squareSize+1;row++) {
            for(int col=1;col < squareSize+1;col++) {
                // IMG_ARRAY[i][j] = rand()%2; 
                // For every cell we need to count the number of live neighbors
                numNeighbors = getLiveNeighbors(IMG_ARRAY, row, col);
                // cin.ignore();
                // cout << "row: " << row << " col: " << col << " Neighbors:" << numNeighbors << endl;
                if(IMG_ARRAY[row][col] && numNeighbors == 0){
                    tempArray[row][col] = 0;
                    continue;
                }
                if(IMG_ARRAY[row][col] && numNeighbors == 1){
                    tempArray[row][col] = 0;
                    continue;
                }
                if(IMG_ARRAY[row][col] && numNeighbors == 2){
                    tempArray[row][col] = 1;
                    continue;
                }
                if(IMG_ARRAY[row][col] && numNeighbors == 3){
                    tempArray[row][col] = 1;
                    continue;
                }
                if(IMG_ARRAY[row][col] && numNeighbors >= 4){
                    tempArray[row][col] = 0;
                    continue;
                }
                if(!IMG_ARRAY[row][col] && numNeighbors == 3){
                    tempArray[row][col] = 1;
                    continue;
                }
            }
        }

        // for(int row=0;row < squareSize+2;row++) {
        //     for(int col=0;col < squareSize+2;col++) {
        //         cout << tempArray[row][col] << " ";
        //     }
        //     cout << endl;
        // }

        for(int row=1;row < squareSize+1;row++) {
            for(int col=1;col < squareSize+1;col++) {
                IMG_ARRAY[row][col] = tempArray[row][col];
                tempArray[row][col] = 0;
            }
        }

        if(k%1 == 0){
            numericInput << k;
            fileNameNumber = numericInput.str();

            trueFileName = fileName + fileNameNumber + fileNameTermination;

            ofstream outputFile;  
            outputFile.open(trueFileName.c_str());
            outputFile << "P3\r\n";
            outputFile << squareSize+2;
            outputFile << " ";
            outputFile << squareSize+2;
            outputFile << "\r\n";
            outputFile << "255\r\n";

            for(int row=0;row < squareSize+2;row++) {
                for(int col=0;col < squareSize+2;col++) {
                    if(IMG_ARRAY[row][col]){
                        outputFile << "0 0 0 "; 
                    }
                    else {
                        outputFile << "255 255 255";
                    }
                    outputFile << " ";
                }
                outputFile << "\r\n";
            }
            outputFile.close();  // we close our file
            numericInput.str("");
        }

        
    }

    MPI_Finalize();
    return 0;
}