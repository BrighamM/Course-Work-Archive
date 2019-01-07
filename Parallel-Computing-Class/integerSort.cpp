#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv){

    int rank; 
    int size;
    int workToDo;
    MPI_Status mesgInfo;
    int horseStatus;
    int numHorses;




    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 

//    MPI_Send(&rank,1,MPI_INT,(rank+1)%size,0,MCW);
//    MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);

    numHorses = size-1;

    if(rank==0) {  // I am the master
        for(int i=1; i<size; ++i){
            workToDo=rand()%10+1;
            cout << "the pig is directing horse "<<i<<" to do "<<workToDo<<" units of work.\n";
            MPI_Send(&workToDo,1,MPI_INT,i,0,MCW);
        }
        while(numHorses>0){
            MPI_Recv(&horseStatus,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,&mesgInfo);
            if(horseStatus!=0){
                cout << "horse "<<mesgInfo.MPI_SOURCE<<" lives to work again.\n";
                workToDo=rand()%10+1;
                cout << "the pig is redirecting horse "<<mesgInfo.MPI_SOURCE<<" to do "<<workToDo<<" units of work.\n";
                MPI_Send(&workToDo,1,MPI_INT,mesgInfo.MPI_SOURCE,0,MCW);
                
            } else {
                cout << "horse "<<mesgInfo.MPI_SOURCE<<" has sacrificed his bones and hoofs for the greater good.\n";
                numHorses--;
            }
            
        }

    } else {  // I am a slave
        horseStatus=1;
        while(horseStatus!=0){
            MPI_Recv(&workToDo,1,MPI_INT,0,0,MCW,MPI_STATUS_IGNORE);
            cout << "horse "<<rank<<" is working."<<endl;
            sleep(workToDo);
            cout << "horse "<<rank<<" is very tired."<<endl;
            horseStatus=rand()%5;
            MPI_Send(&horseStatus,1,MPI_INT,0,0,MCW);
        }

    }

    MPI_Finalize();

    return 0;
}
/**
 * First this should randomly generate an array
 * 
 * 
 */