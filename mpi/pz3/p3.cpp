#include <mpi.h>
#include <iostream>

using namespace std;
using namespace MPI;


const int SIZE = 10000000;

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

    // Create vector and init for root process
    double* vec = world_rank == 0 ? create_vec(SIZE) : NULL;
    double* vec_part = new double[SIZE / world_size];

    // Split vector to equal parts and send them to different processes
    int size = SIZE / world_size;
    MPI_Scatter(vec, size, DOUBLE, vec_part, size, DOUBLE, 0, MPI_COMM_WORLD);

    // Get scalar multiplication for the part of gotten vector
    int sum = get_scalar(vec_part, size); 

    // Create array of sums to merge them all
    int* sums = world_rank == 0 ? new int[world_size] : NULL;

    // Merge sums
    MPI_Gather(&sum, 1, INT, sums, 1, INT, 0, MPI_COMM_WORLD);

    // Summarize result and output it
    if (world_rank == 0)
    {
        sum = 0;
        for (int i = 0; i < world_size; i++)
            sum += sums[i];
        cout << sum << endl;
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
