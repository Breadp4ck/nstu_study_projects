#include <mpi.h>
#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;


const long long SIZE = 100000;

void fill_vec(double* vec);
double vec_norm(double* vec);


int main(int argc, char** argv)
{
    double* vec = new double[SIZE];
    MPI_Status stat;
    double norm;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0)
    {
        int cnt = world_size - 1;
        int* ranks = new int[cnt];
        MPI_Request* requests = new MPI_Request[cnt];

        for (int i = 0; i < cnt; i++)
        {
            ranks[i] = i + 1;
            MPI_Irecv(&norm, 1, MPI_DOUBLE, ranks[i], 0, MPI_COMM_WORLD, &(requests[i]));
        }

        while (cnt > 0)
            for (int i = 0; i < cnt; i++)
            {
                int flag = 0;

                MPI_Test(&(requests[i]), &flag, &stat);

                if (flag)
                {
                    cout << "rank " << ranks[i] << ":\t" << norm << endl;

                    for (int ii = i; ii < cnt-1; ii++)
                    {
                        requests[ii] = requests[ii+1];
                        ranks[ii] = ranks[ii+1];
                    }
                    cnt--;
                }
            }
    }
    else
    {
        fill_vec(vec);
        norm = vec_norm(vec);
        MPI_Send(&norm, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}


void fill_vec(double* vec)
{
    for (int i = 0; i < SIZE; i++)
        vec[i] = rand() % 10;
}


double vec_norm(double* vec)
{
    double norm = 0;

#pragma omp for
    for (int i = 0; i < SIZE; i++)
        norm += pow(vec[i], 2);

    norm = sqrt(norm);

    return norm;
}
