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

    // Generate random number for every process
    srand(time(0) + world_rank);
    int number = rand() % 10;

    // Create buffer and init it only for root process
    int* numbers = world_rank == 0 ? new int[world_size] : NULL;

    // Send generated numbers to root process
    MPI_Gather(&number, 1, INT, numbers, 1, INT, 0, MPI_COMM_WORLD);

    // Output the sum of gotten numbers
    if (world_rank == 0)
    {
        int sum = 0;
        for (int i = 0; i < world_size; i++)
            sum += numbers[i];
        cout << sum << endl;
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
