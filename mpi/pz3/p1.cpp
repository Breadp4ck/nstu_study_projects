#include <mpi.h>
#include <iostream>

using namespace std;
using namespace MPI;


int main(int argc, char** argv)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get number from console for root process
    int number;
    if (world_rank == 0) cin >> number;

    // Send the number from root process to all another
    MPI_Bcast(&number, 1, DOUBLE, 0, MPI_COMM_WORLD);

    // Output the number and the process name
    cout << world_rank << ": " << number << endl;

    // Finalize the MPI environment.
    MPI_Finalize();
}
