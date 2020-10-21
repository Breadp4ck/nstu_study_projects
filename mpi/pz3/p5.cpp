#include <mpi.h>
#include <iostream>
#include <cmath>

using namespace std;


const long long SIZE = 10;

void fill_vec(double* vec);
double vec_multiply(double* vec1, double* vec2);
double vec_norm(double* vec);
void fill_matrix(double* matrix);


int main(int argc, char** argv)
{
    double* vec1 = new double[SIZE];
    double* vec2 = new double[SIZE];
    double* matrix = new double[SIZE * SIZE];

    fill_vec(vec1);
    fill_matrix(matrix);

    MPI_Status stat;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int* divider = new int[world_size];
    int* offsets = new int[world_size];

    for (int i = 0; i < world_size; i++)
    {
        divider[i] = (SIZE / world_size + (SIZE % world_size > i ? 1 : 0)) * SIZE;
        if (world_rank == 0) cout << divider[i] << " ";
    }

    double* vec2_part = new double[divider[world_rank]];

    // TODO
    // Сделать пиздато
    //MPI_Scatter(matrix, divider, MPI_DOUBLE, MPI_COMM_WORLD);

    //double* vec_rec = new double[SIZE];
    //double sum;

    //for (int i = 0; i < SIZE; i += world_size) 
    //{
    //        MPI_Scatter(&matrix[i], SIZE, MPI_DOUBLE, vec_rec, SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    //        vec2[i + world_rank] = vec_multiply(vec_rec, vec1);

    //        cout << i + world_rank << " ";
    //}

    //if (world_rank == 0)
    //{
    //    for (int i = 0; i < SIZE; i++)
    //        cout << vec2[i] << "\n";
    //}
    //// Finalize the MPI environment.
    MPI_Finalize();
}


void fill_vec(double* vec)
{
    for (int i = 0; i < SIZE; i++)
        vec[i] = rand() % 10;
}


void fill_matrix(double* matrix)
{
    for (int i = 0; i < SIZE * SIZE; i++)
        matrix[i] = rand() % 10;
}


double vec_multiply(double* vec1, double* vec2)
{
    double sum = 0;

    for (unsigned int i = 0; i < SIZE; i++)
        sum += vec1[i] * vec2[i];

    return sum;
}
