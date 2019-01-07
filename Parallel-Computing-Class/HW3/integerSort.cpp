#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#define MCW MPI_COMM_WORLD

using namespace std;

void mergeSortLastPart(){

}

int main(int argc, char **argv){

    int worldRank; 
    int worldSize;
    srand((unsigned)time(0));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &worldRank); 
    MPI_Comm_size(MCW, &worldSize); 

    // MPI_Send(&rank,1,MPI_INT,(rank+1)%size,0,MCW);
    // MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);

    // First lets create a vector of random ints.
    int totalElements = 12;

    int elements_per_proc = totalElements/worldSize;

    int *rand_nums = (int*)malloc(sizeof(int) * totalElements);
    int *sub_rand_nums = (int*)malloc(sizeof(int) * elements_per_proc);

    if(worldRank == 0){
        cout << "Here we show the preiminary unsorted array." << endl;
        for(int i = 0; i < totalElements; i++){
            rand_nums[i] = rand()%1000;
            cout << rand_nums[i] << endl;
        }
    }

    MPI_Scatter(
        rand_nums,
        elements_per_proc,
        MPI_INT,
        sub_rand_nums,
        elements_per_proc,
        MPI_INT,
        0,
        MCW
    );
    

    if(worldRank == 0){
        sleep(5);
        cout << "The unsorted array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
        sort(sub_rand_nums, sub_rand_nums + elements_per_proc);
        cout << "The SORTED array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
            
    }
    if(worldRank == 1){
        sleep(10);
        cout << "The unsorted array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
        sort(sub_rand_nums, sub_rand_nums + elements_per_proc);
        cout << "The SORTED array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
    }
    if(worldRank == 2){
        sleep(15);
        cout << "The unsorted array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
        sort(sub_rand_nums, sub_rand_nums + elements_per_proc);
        cout << "The SORTED array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
    }
    if(worldRank == 3){
        sleep(20);
        cout << "The unsorted array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
        sort(sub_rand_nums, sub_rand_nums + elements_per_proc);
        cout << "The SORTED array for PROC: " << worldRank << " is:" << endl;
        for (int i = 0; i < elements_per_proc; i++){
            cout << "PROC: " << worldRank << " val: " << sub_rand_nums[i] << endl;
        }
    }
    int *sub_sorted_array = NULL;
    if(worldRank == 0){
        sub_sorted_array = (int*)malloc(sizeof(int) * totalElements);
    }
   

    MPI_Gather(
        sub_rand_nums, 
        elements_per_proc, 
        MPI_INT, 
        sub_sorted_array, 
        elements_per_proc, 
        MPI_INT, 
        0,
        MCW
    );

    if(worldRank == 0){
        cout << "The partially SORTED array for every processoror is:" << endl;
        for (int i = 0; i < totalElements; i++){
            cout << "VALUE: " << sub_sorted_array[i] << endl;
        }
        sort(sub_sorted_array, sub_sorted_array + totalElements);
        cout << "The Final SORTED array for every processor is:" << endl;
        for (int i = 0; i < totalElements; i++){
            cout << "PROC: " << worldRank << " val: " << sub_sorted_array[i] << endl;
        }

    }




    MPI_Finalize();

    return 0;
}