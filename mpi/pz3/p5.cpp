#include <mpi.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace MPI;


const int SIZE = 10;

double* create_vec(int size);
double vec_multiply(double* vec1, double* vec2, int length);
double* create_matrix(int size);


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

    // Create vectors and matrix
    double* vec1;
    double* vec2;
    double* matrix;

    // Create arrays with vector sizes and displacements
    int* field_cnts; 
    int* row_cnts;
    int* field_disps;
    int* row_disps;

    // Create and init needed rows of matrix for each process
    int row_cnt = SIZE / world_size + ((SIZE % world_size) > world_rank ? 1 : 0);
    int fields_cnt = row_cnt * SIZE;
    double* rows = new double[row_cnt * SIZE];

    // Init needed values
    if (world_rank == 0)
    {
        // Init vectors and matrix
        vec1 = create_vec(SIZE);
        vec2 = new double[SIZE];
        matrix = create_matrix(SIZE);

        field_cnts = new int[world_size];
        row_cnts = new int[world_size];

        field_disps = new int[world_size];
        row_disps = new int[world_size];

        int row_sum = 0;

        for (int i = 0; i < world_size; i++)
        {
            row_cnts[i] = SIZE / world_size + ((SIZE % world_size) > i ? 1 : 0);
            field_cnts[i] = row_cnts[i] * SIZE;

            row_disps[i] = row_sum;
            field_disps[i] = row_sum * SIZE;

            row_sum += row_cnts[i];
        }
    }
    else
    {
        vec1 = new double[SIZE];
    }

    //// Send rows to processes
    MPI_Scatterv(matrix, field_cnts, field_disps, DOUBLE, rows, row_cnt * SIZE, DOUBLE, 0, MPI_COMM_WORLD);

    //// Send multiplied vector to each process
    MPI_Bcast(vec1, SIZE, DOUBLE, 0, MPI_COMM_WORLD);

    //// Create part for result vector for each process
    double* vec2_part = new double[row_cnt];

    for (int i = 0; i < row_cnt; i++)
        vec2_part[i] = vec_multiply(&rows[i * SIZE], vec1, SIZE);

    // Sends rows to root process
    MPI_Gatherv(vec2_part, row_cnt, DOUBLE, vec2, row_cnts, row_disps, DOUBLE, 0, MPI_COMM_WORLD);

    // Output the result
    if (world_rank == 0)
        for (int i = 0; i < SIZE; i++)
            cout << vec2[i] << "\n";

    // Finalize the MPI environment.
    MPI_Finalize();
}

// Fill vector with random numbers
double* create_vec(int size)
{
    double* vec = new double[size];

    for (int i = 0; i < size; i++)
        vec[i] = rand() % 10;

    return vec;
}

// Fill matrix with random numbers
double* create_matrix(int size)
{
    int length = size * size;
    double* matrix = new double[length];

    for (int i = 0; i < length; i++)
        matrix[i] = rand() % 10;

    return matrix;
}

// Multiply two vectors
double vec_multiply(double* vec1, double* vec2, int length)
{
    double sum = 0;

    for (unsigned int i = 0; i < length; i++)
        sum += vec1[i] * vec2[i];

    return sum;
}
