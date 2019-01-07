#include <iostream>
#include <mpi.h>
#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv){
	
	int rank;
	int size;
	int data;
	// These are the six favorites
	// when you send a message the contents of the buffer are written to an internal mpi send/receive buffer
	// &rank in send is a locally blocking send.
	/**
	 * Send is not globally blocking, it is not gauranteed that the receiving process has recieved it
	 * the only gaurantee is that the buffer is free to use now.
	 * 
	 * look up a tutorial
	 * 
	 * look up the args for send and recieve. we are just concerned with ints and maybe floats 
	 * 
	 * 
	 * 
	 */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MCW, &rank);
	MPI_Comm_size(MCW, &size);

	MPI_Send(&rank,1,MPI_INT,(rank + 1)%size,0,MCW);

	/**
	 * understand precedence of what happens in an order. 
	 * 
	 * &data is a locally blocking receive operations again you need to go over the parameters
	 */
	MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);


	cout << "I am " << rank << " of " << size << "; got a message from " << data << endl;

	MPI_Finalize();

	return 0;

	
}
