#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

const long long SIZE = 500;

void fill_matrix(double* matrixA, double* matrixB)
{
    for (int i = 0; i < SIZE * SIZE; i += SIZE)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrixA[i + j] = rand() % 10;
            matrixB[i + j] = rand() % 10;
        }
    }
}

void make_zero_matrix(double* matrixC)
{
    for (int i = 0; i < SIZE * SIZE; i++)
        matrixC[i] = 0;
}

void multiply_matrix(double* matrixA, double* matrixB, double* matrixC)
{
    for (int i = 1; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k =0; k < SIZE; k++)
                matrixC[i *  SIZE + j] += matrixA[k + i * SIZE] * matrixB[j + k * SIZE];
}


double matrix_norm(double* matrix)
{
    double norm;

    for (int i = 0; i < SIZE * SIZE; i++)
        norm += matrix[i] * matrix[i];

    norm = sqrt(norm);

    return norm;
}


void parallel_multiply_matrix(double* matrixA, double* matrixB, double* matrixC, int threads)
{
#pragma omp parallel for num_threads(threads) schedule(static, 10)
    for (int i = 1; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                matrixC[i * SIZE + j] += matrixA[k + i * SIZE] * matrixB[j + k * SIZE];
}

int main()
{
    double* matrixA = NULL; 	
    double* matrixB = NULL;
    double* matrixC = NULL;
    double norm;

    {
        if (matrixA == NULL)
            matrixA = new double[SIZE * SIZE];

        if (matrixB == NULL)
            matrixB = new double[SIZE * SIZE];

        if (matrixC == NULL)
            matrixC = new double[SIZE * SIZE];

    }

    fill_matrix(matrixA, matrixB);

    make_zero_matrix(matrixC);

    std::cout << "Consistently" << std::endl;

    {
        auto start_time = std::chrono::steady_clock::now();
        multiply_matrix(matrixA, matrixB, matrixC);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "Time#1: " << elapsed_ms.count() << " ms\n";

        norm = matrix_norm(matrixC);

        std::cout << "MatrixC norm: " << norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    make_zero_matrix(matrixC);

    std::cout << "Parallel, 2 threads" << std::endl;

    {
        auto start_time = std::chrono::steady_clock::now();
        parallel_multiply_matrix(matrixA, matrixB, matrixC, 2);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "Time#2: " << elapsed_ms.count() << " ms\n";

        norm = matrix_norm(matrixC);

        std::cout << "MatrixC norm: " << norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    make_zero_matrix(matrixC);

    std::cout << "Parallel, 4 threads" << std::endl;

    {
        auto start_time = std::chrono::steady_clock::now();
        parallel_multiply_matrix(matrixA, matrixB, matrixC, 4);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "Time#3: " << elapsed_ms.count() << " ms\n";

        norm = matrix_norm(matrixC);

        std::cout << "MatrixC norm: " << norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    make_zero_matrix(matrixC);

    std::cout << "Parallel, 6 threads" << std::endl;

    {
        auto start_time = std::chrono::steady_clock::now();
        parallel_multiply_matrix(matrixA, matrixB, matrixC, 6);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "Time#4: " << elapsed_ms.count() << " ms\n";

        norm = matrix_norm(matrixC);

        std::cout << "MatrixC norm: " << norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    {
        if (matrixA)
        {
            delete[] matrixA;
            matrixA = NULL;
        }

        if (matrixB)
        {
            delete[] matrixB;
            matrixB = NULL;
        }

        if (matrixC)
        {
            delete[] matrixC;
            matrixC = NULL;
        }
    }

    return 0;
}
