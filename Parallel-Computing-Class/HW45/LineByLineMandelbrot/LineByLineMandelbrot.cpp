/**
 * Code used and referenced from
 * https://www.tankonyvtar.hu/hu/tartalom/tamop412A/2011-0063_23_introduction_mpi/ar01s12.html
 * 
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h> 
#include <vector>
#include <time.h>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

using namespace std;
const int PIXELS_IN_X=2048; 
const int PIXELS_IN_Y=2048; 
const int MAX_ITERS=3000; 
const double Y_MIN= -0.135; 
const double Y_MAX= -0.115;
const double X_MIN= -0.79; 
const double X_MAX= -0.77;
int IMG_ARRAY[PIXELS_IN_X][PIXELS_IN_Y] = {0}; 
int IMG_LINE[PIXELS_IN_Y] = {0};

int mandelbrot_Iterations(double calcd_xPos,double calcd_yPos)
{
	int iters = 0;
	double zx = 0;
	double x_Temp = 0;
	double zy = 0;
	while( (iters < MAX_ITERS) && (zx * zx + zy * zy) < 4 ) {
		x_Temp = zx*zx - zy*zy + calcd_xPos;
		zy = 2*zx*zy + calcd_yPos;
		zx = x_Temp;
		iters++;
	}
	return iters;
}
  

int main(int argc, char **argv) {
    int myRank;
    int worldSize;
    MPI_Status mpiStatus;
    int answer[2];
    double question;

    double pixelWidthInX = 0;
    double pixelWidthInY = 0;
    double calcd_xPos=X_MIN; 
    double calcd_yPos=Y_MIN;

    double startTime;
    double endTime; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &myRank);
    MPI_Comm_size(MCW, &worldSize);
    MPI_Barrier(MCW); 


    if(myRank == 0) { //Master

        if(argc<2) {
            cout << "You probably need to specify the output file." << endl;
            cout << argv[0] << " out_file.ppm " << endl;
            MPI_Abort(MCW, 1);
            exit(1);
        }

        ofstream myfile; 
        string filename1(argv[1]);
        char *fileName1 = (char*)filename1.c_str();

        pixelWidthInX = (X_MAX-X_MIN) / PIXELS_IN_X;
        pixelWidthInY = (Y_MAX-Y_MIN) / PIXELS_IN_Y;

        startTime=MPI_Wtime(); // we get a time value at this point

        for(int i = 0; i < PIXELS_IN_X; i++) {
            MPI_Recv(answer, 2, MPI_INT, MPI_ANY_SOURCE, 1, MCW, &mpiStatus);
            // answer[0] -- from whom
            // answer[1] -- '-1' or the X coordinate

            if(answer[1] >= 0) { //not the first answer
                MPI_Recv(&IMG_ARRAY[answer[1]][0], PIXELS_IN_Y, MPI_INT, answer[0], 2, MCW, &mpiStatus);
            }
            MPI_Send(&i, 1, MPI_INT, answer[0], 3, MCW);
            MPI_Send(&calcd_xPos, 1, MPI_DOUBLE, answer[0], 4, MCW);
            calcd_xPos = calcd_xPos + pixelWidthInX;
        }

        int term = -1;
        for(int i = 1; i < worldSize; ++i) {
            MPI_Recv(answer, 2, MPI_INT, MPI_ANY_SOURCE, 1, MCW, &mpiStatus);
            MPI_Recv(&IMG_ARRAY[answer[1]][0], PIXELS_IN_Y, MPI_INT, answer[0], 2, MCW, &mpiStatus);

            //sending the termination signal
            MPI_Send(&term, 1, MPI_INT, answer[0], 3, MCW);
        }

        // we get another time at this point, so we can calculate the elapsed time for the calculation
        endTime=MPI_Wtime();

        cout << "Time elapsed during calculation: " << endTime - startTime << " secs." << endl;;

        // file IO
        myfile.open(fileName1);
        myfile << "P3\r\n";
        myfile << PIXELS_IN_X;
        myfile << " ";
        myfile << PIXELS_IN_Y;
        myfile << "\r\n";
        myfile << "255\r\n";

        for(int i = 0; i < PIXELS_IN_X; i++) {
            for(int j = 0; j < PIXELS_IN_Y; j++) {
                if( (IMG_ARRAY[i][j] < 256) ) {
                    myfile << IMG_ARRAY[i][j] << " 0 0";
                }
                else if( IMG_ARRAY[i][j] < 512) {
                    myfile << "255 " << IMG_ARRAY[i][j] - 256 << " 0";
                }
                else if( IMG_ARRAY[i][j] < 768) {
                    myfile << "255 255 " << IMG_ARRAY[i][j] - 512;
                }
                else {
                    myfile << "0 0 0 ";
                } 
                myfile << " ";
            }
            myfile << "\r\n";
        }
        myfile.close();  // we close our file
        endTime=MPI_Wtime(); // and give another elapsed time info (IO included)
        cout << "Time elapsed total (computation + color + file output): " << endTime - startTime << " secs \r\n";
    }

    else { //Slave
        pixelWidthInX = (X_MAX-X_MIN) / PIXELS_IN_X;
        pixelWidthInY = (Y_MAX-Y_MIN) / PIXELS_IN_Y;

        int i;
        answer[0] = myRank;
        answer[1] = -1;
        MPI_Send(answer, 2, MPI_INT, 0, 1, MCW);

        while(1){
            MPI_Recv(&i, 1, MPI_INT, 0, 3, MCW, &mpiStatus);
            if(i < 0) {
                break; //got termination command!
            } 
            answer[1] = i;
            MPI_Recv(&question, 1, MPI_DOUBLE, 0, 4, MCW, &mpiStatus);
            calcd_yPos = Y_MIN;  // at every new step in X direction, we start at the first Y value 
            for(int j = 0; j < PIXELS_IN_Y; j++) {
                IMG_LINE[j] = mandelbrot_Iterations(question, calcd_yPos);
                calcd_yPos = calcd_yPos + pixelWidthInY;
            }
            MPI_Send(answer, 2, MPI_INT, 0, 1, MCW);
            MPI_Send(IMG_LINE, PIXELS_IN_Y, MPI_INT, 0, 2, MCW);
        }
    }
    // Terminate MPI
    MPI_Finalize();
    return 0;
 }