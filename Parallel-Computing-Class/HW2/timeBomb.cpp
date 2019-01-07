#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv){

    int rank;
    int size;
    int eliminatedProcess = -1;
    srand(time(0));
    int bombTimer=rand()%20 + 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 
    /**
     * Remember!
     * 
     * MPI_Send(
     * void* data,
     * int count,
     * MPI_Datatype datatype,
     * int destination,
     * int tag,
     * MPI_Comm communicator 
     * ); 
     * 
     **/

    /**
     * And dont forget!
     * 
     * MPI_Recv(
     * void* data,
     * int count,
     * MPI_Datatype datatype,
     * int source,
     * int tag,
     * MPI_Comm communicator,
     * MPI_Status* status
     * )
     * 
     **/



    if(rank==0){
        // We are adding more logic so that we do not pass the bomb to ourselves.
        int nextPassedPlayer = rand()%size;
        while(nextPassedPlayer == 0){
            nextPassedPlayer = rand()%size;
        }
        cout<<"*******************************************************"<<endl;
        cout<<"*      WE ARE NOW BEGINNING THE TIME BOMB GAME!!!     *"<<endl;
        cout<<"*      GAME STATS:                                    *"<<endl;
        cout<<"*      NUMBER OF PLAYERS: "<<size<<"                           *"<<endl;
        cout<<"*      STARTING BOMB TIME :"<<bombTimer<<"                         *"<<endl;
        cout<<"*           BEGIN THE GAME!!!!!!!!!                   *"<<endl;
        cout<<"*******************************************************"<<endl;

        cout<<"I am process "<<rank<<" and the bomb timer is at: "<<bombTimer<<" Passing to: "<<nextPassedPlayer<<endl;

        MPI_Send(&bombTimer,1,MPI_INT,nextPassedPlayer,0,MCW);
    }

    while(true){
        // Run until the bomb expl
        MPI_Recv(&bombTimer,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);
        if(!bombTimer){
            cout << rank << ": all done."<<endl;
            break;
        }
        // decrement the bomb timer
        bombTimer--;
        cout<<"I am process "<<rank<<" and the bomb timer is at: "<<bombTimer<<endl;
        if(bombTimer == 0){
            eliminatedProcess = rank;
        }
        


        if(!bombTimer){
            for(int i=0;i<size;++i){
                MPI_Send(&bombTimer,1,MPI_INT,i,0,MCW);
            }
        }
        // We are not passing the bomb off to our selves. That is stupid! 
        // Thats like taking two turns in a row a Russian Roulette!
        int passToPlayer = rand()%size;
        while(passToPlayer == rank){
            passToPlayer = rand()%size;
        }
        MPI_Send(&bombTimer,1,MPI_INT,passToPlayer,0,MCW);
    }

    if(rank == eliminatedProcess){
        cout<<"*******************************************************"<<endl;
        cout<<"*             THE GAME IS OVER!!!                     *"<<endl;
        cout<<"*      PROCESS: "<<eliminatedProcess<<" HAS BEEN ELIMINATED!!!              *"<<endl;
        cout<<"*******************************************************"<<endl;
    }

    MPI_Finalize();

    return 0;
}