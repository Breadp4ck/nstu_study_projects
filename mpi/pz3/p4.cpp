#include <mpi.h>
#include <iostream>

using namespace std;
using namespace MPI;


const int SIZE = 9999999;

double* create_vec(int size);
double get_scalar(double* vec, int length);


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

    // Create main vector and init for root process
    double* vec = world_rank == 0 ? create_vec(SIZE) : NULL;

    // Create and init size of subvector for every single process
    int vec_size = SIZE / world_size + ((SIZE % world_size) > world_rank ? 1 : 0);
    double* vec_part = new double[vec_size];

    // Create arrays with vector sizes and displacements and init it for root process
    int* vec_sizes; int* disps;
    if (world_rank == 0)
    {
        vec_sizes = new int[world_size];
        disps = new int[world_size];
        int sum = 0;

        for (int i = 0; i < world_size; i++)
        {
            vec_sizes[i] = SIZE / world_size + ((SIZE % world_size) > i ? 1 : 0);
            disps[i] = sum;
            sum += vec_sizes[i];
        }
    }

    // Split and send subvectors to processes
    MPI_Scatterv(vec, vec_sizes, disps, DOUBLE, vec_part, vec_size, DOUBLE, 0, MPI_COMM_WORLD);

    // Get scalar multiplication for the part of gotten vector
    double scalar = get_scalar(vec_part, vec_size); 

    // Create array of sums to merge them all
    double* scalars = world_rank == 0 ? new double[world_size] : NULL;

    // Merge sums
    MPI_Gather(&scalar, 1, DOUBLE, scalars, 1, DOUBLE, 0, MPI_COMM_WORLD);

    // Summarize result and output it
    if (world_rank == 0)
    {
        scalar = 0;
        for (int i = 0; i < world_size; i++)
            scalar += scalars[i];
        cout << scalar << endl;
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}

// Get ref to vector and return ref to the same vector
double* create_vec(int size)
{
    double* vec = new double[size];

    for (int i = 0; i < SIZE; i++)
        vec[i] = rand() % 10;

    return vec;
}

// Get scalar multiplication of vector
double get_scalar(double* vec, int length)
{
    double scalar = 0;

    for (int i = 0; i < length; i++)
        scalar += vec[i] * vec[i];

    return scalar;
}
