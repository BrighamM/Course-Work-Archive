
#include <stdlib.h>
#include <queue> 
#include <iostream>
#include <mpi.h>
#include <unistd.h>
#define MCW MPI_COMM_WORLD
#define ANYSOURCE MPI_ANY_SOURCE
#define JOB 1
#define TOKEN 2
#define KILLSWITCH 3
#define WHITE 4
#define BLACK 5

using namespace std;

void processTask(int inputInt) {
    int squareValue = inputInt * inputInt;
    for(int i = 0; i < squareValue; i++){
        inputInt++;
    }
    return;
}

int main(int argc, char **argv){

    int myRank, worldSize;
    int data;
    int newJobReceived;
    int jobToSend;
    int jobReceivedFlag; 
    int tokenReceivedFlag;
    int tokenReceived;
    int tokenToSend;
    int killToSend;
    int killToRecv;
    int killReceivedFlag;
    MPI_Request myRequest;
    MPI_Status myStatus;
    int numTasksThatWillBeGenerated;
    bool iPossessTheToken;
    bool finishedGeneratingTasks;
    bool iAmBlackProcess = true;
    int totalNumberOfTasksToGenerate = 0;
    int numberOfTasksGenerated = 0;
    queue<int> myWorkQueue;
    int rankToSendTo;
    int dest1, dest2;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &myRank); 
    MPI_Comm_size(MCW, &worldSize); 

    sleep((unsigned int)myRank*3);

    srand(time(0));
    totalNumberOfTasksToGenerate = 1024 + (rand()%1024);
    iPossessTheToken = false;
    tokenToSend = WHITE;
    tokenReceived = BLACK;
    finishedGeneratingTasks = false;
    iAmBlackProcess = false;
    killToRecv = 99;

    cout << "p: " << myRank << " tot:" << totalNumberOfTasksToGenerate << endl; 
//    MPI_Send(&myRank,1,MPI_INT,(myRank+1)%worldSize,0,MCW);
//    MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);

    if(myRank == 0){
        iPossessTheToken = true;
    }

    MPI_Barrier(MCW);
    sleep(1);
    MPI_Barrier(MCW);

    while(killToRecv > 0) {

        if(myRank == 0){
            cin.ignore();
            cout << "Proc:" << myRank << " isBlack?:" << iAmBlackProcess << " isFin?:" << finishedGeneratingTasks << " Token?:" << iPossessTheToken << " Size:" << myWorkQueue.size() << " TasksGend/Total: " << numberOfTasksGenerated << "/" << totalNumberOfTasksToGenerate << endl; 
        }
        MPI_Barrier(MCW);
        if(myRank == 1){
            // cin.ignore();
            cout << "Proc:" << myRank << " isBlack?:" << iAmBlackProcess << " isFin?:" << finishedGeneratingTasks << " Token?:" << iPossessTheToken << " Size:" << myWorkQueue.size() << " TasksGend/Total: " << numberOfTasksGenerated << "/" << totalNumberOfTasksToGenerate << endl; 
        }
        MPI_Barrier(MCW);
        if(myRank == 2){
            // cin.ignore();
            cout << "Proc:" << myRank << " isBlack?:" << iAmBlackProcess << " isFin?:" << finishedGeneratingTasks << " Token?:" << iPossessTheToken << " Size:" << myWorkQueue.size() << " TasksGend/Total: " << numberOfTasksGenerated << "/" << totalNumberOfTasksToGenerate << endl; 
        }
        MPI_Barrier(MCW);
        if(myRank == 3){
            // cin.ignore();
            cout << "Proc:" << myRank << " isBlack?:" << iAmBlackProcess << " isFin?:" << finishedGeneratingTasks << " Token?:" << iPossessTheToken << " Size:" << myWorkQueue.size() << " TasksGend/Total: " << numberOfTasksGenerated << "/" << totalNumberOfTasksToGenerate << endl; 
        }
        MPI_Barrier(MCW);

        // CHECK FOR INCOMING MESSAGES.
        while(1){
            MPI_Iprobe(ANYSOURCE,JOB,MCW,&jobReceivedFlag,&myStatus);
            if(!jobReceivedFlag)break;
            MPI_Recv(&newJobReceived,1,MPI_INT,ANYSOURCE,JOB,MCW,&myStatus);
            if(myStatus.MPI_SOURCE > myRank){
                iAmBlackProcess = true;
            }
            myWorkQueue.push(newJobReceived);
        }

        MPI_Barrier(MCW);

        // CHECK IF I RECEIVED THE TOKEN.
        while(1){
            MPI_Iprobe(ANYSOURCE,TOKEN,MCW,&tokenReceivedFlag,&myStatus);
            if(!tokenReceivedFlag)break;
            MPI_Recv(&tokenReceived,1,MPI_INT,ANYSOURCE,TOKEN,MCW,&myStatus);
            iPossessTheToken = true;
            if(tokenReceived == WHITE && (myRank == 0)){
                killToSend = -99;
                for (int i = 0; i < worldSize; i++) {
                    MPI_Send(&killToSend,1,MPI_INT,i,KILLSWITCH,MCW);
                }
                cout << "TERMINATION" << endl;
            }
        }

        MPI_Barrier(MCW);

        // CHECK IF I RECEIVED THE Kill Signal.
        while(1){
            MPI_Iprobe(ANYSOURCE,KILLSWITCH,MCW,&killReceivedFlag,&myStatus);
            if(!killReceivedFlag)break;
            MPI_Recv(&killToRecv,1,MPI_INT,ANYSOURCE,KILLSWITCH,MCW,&myStatus);
        }

        MPI_Barrier(MCW);

        // The next step is: if i have more than 16 tasks in my queue then I am going to send those to other procs.
        if(myWorkQueue.size() > 16){
            jobToSend = myWorkQueue.front();
            MPI_Send(&jobToSend,1,MPI_INT,rand()%worldSize,JOB,MCW);
            myWorkQueue.pop();
            jobToSend = myWorkQueue.front();
            MPI_Send(&jobToSend,1,MPI_INT,rand()%worldSize,JOB,MCW);
            myWorkQueue.pop();
        }

        // Perform some work....
        if(!myWorkQueue.empty()){
            processTask(myWorkQueue.front());
            myWorkQueue.pop();
        }

        // generate 1-3 new tasks and place them at the end of my process queue.
        if(!finishedGeneratingTasks){
            numTasksThatWillBeGenerated = rand()%3 + 1;
            for(int i = 0; i < numTasksThatWillBeGenerated; i++){
                // generate a task
                myWorkQueue.push(rand()%1024 + 1);
                numberOfTasksGenerated++;
            }
            if(numberOfTasksGenerated >= totalNumberOfTasksToGenerate){
                finishedGeneratingTasks = true;
            }
        }

        if(finishedGeneratingTasks && myWorkQueue.empty() && iPossessTheToken && (myRank == 0)){
            // Pass off the token
            iPossessTheToken = false;
            tokenToSend = WHITE;
            iAmBlackProcess = false;
            MPI_Send(&tokenToSend,1,MPI_INT,((myRank + 1)%worldSize),TOKEN,MCW);
            continue;
        }

        if(finishedGeneratingTasks && myWorkQueue.empty() && iPossessTheToken){
            // Pass off the token
            iPossessTheToken = false;
            if(iAmBlackProcess){
                tokenToSend = BLACK;
            }
            iAmBlackProcess = false;
            MPI_Send(&tokenToSend,1,MPI_INT,((myRank + 1)%worldSize),TOKEN,MCW);
            continue;
        }
    }

    MPI_Finalize();

    return 0;
}
