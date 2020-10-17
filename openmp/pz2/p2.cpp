#include <chrono>
#include <omp.h>
#include <iostream>
#include <cmath>
 
const long long  SIZE = 10000;
 
void fill_matrix(double* matrix, long long size)
{
    for (int i = 0; i < size * size; i += size)
        for (int j = 0; j < size; j++)
            matrix[i + j] = rand() % 10;
}
 
void multiplication_parallel6(double* matrix, double* vx, double* vy, long long size)
{
#pragma omp parallel for schedule(static, 10)  num_threads(6)
    for (int i = 0; i < size; i++)
    {
        double sum = 0;
#pragma omp reduction (+: sum)
        for (int j = 0; j < size; j++)
        {
            sum += vx[j] * matrix[i * size + j];
        }
        vy[i] = sum;
    }
}

void multiplication_parallel4(double* matrix, double* vx, double* vy, long long size)
{
#pragma omp parallel for schedule(static, 10)  num_threads(4)
    for (int i = 0; i < size; i++)
    {
        double sum = 0;
#pragma omp reduction (+: sum)
        for (int j = 0; j < size; j++)
        {
            sum += vx[j] * matrix[i * size + j];
        }
        vy[i] = sum;
    }
}
 
void multiplication_parallel2(double* matrix, double* vx, double* vy, long long size)
{
#pragma omp parallel for schedule(static, 10)  num_threads(2)
    for (int i = 0; i < size; i++)
    {
        double sum = 0;
#pragma omp reduction (+: sum)
        for (int j = 0; j < size; j++)
        {
            sum += vx[j] * matrix[i * size + j];
        }
        vy[i] = sum;
    }
}

void multiplication_consistently(double* matrix, double* vx, double* vy, long long size)
{
    for (int i = 0; i < size; i++)
    {
        double sum = 0;
        for (int j = 0; j < size; j++)
        {
            sum += vx[j] * matrix[i * size + j];
        }
        vy[i] = sum;
    }
}
 
 
double function_xvector_norm(double* vx, long long size)
{
    double xvector_norm = 0;
    int i = 0;
 
#pragma omp parallel for shared(i) schedule(static, 10) reduction (+: xvector_norm) num_threads(4)
    for (i = 0; i < size; i++)
        xvector_norm += vx[i] * vx[i];
 
    xvector_norm = sqrt(xvector_norm);
 
    return xvector_norm;
}
 
double function_yvector_norm(double* vy, long long size)
{
    double yvector_norm = 0;
    int i = 0;
 
#pragma omp parallel for shared(i) schedule(static, 10) reduction (+: yvector_norm) num_threads(4)
    for (i = 0; i < size; i++)
        yvector_norm += vy[i] * vy[i];
 
    yvector_norm = sqrt(yvector_norm);
 
    return yvector_norm;
}
 
int main()
{
    double* matrix = NULL;
 
    if (matrix == NULL)
        matrix = new double[SIZE * SIZE];
 
    double* vx = new double[SIZE];
    double* vy = new double[SIZE];
    double sum = 0;
    double xvector_norm = 0;
    double yvector_norm = 0;
    long long size;
 
    std::cout << "Size: ";
    std::cin >> size;
 
    fill_matrix(matrix, size);
 
    for (int i = 0; i < size; i++)
    {
        vx[i] = rand() % 10;
        vy[i] = 0;
    }
 
    std::cout << "--------------" << std::endl;
 
 
    xvector_norm = function_xvector_norm(vx, size);
    std::cout << "Vector<x> norm: " << xvector_norm << std::endl;
 
    std::cout << "--------------" << std::endl;
 
    std::cout << "Consistently" << std::endl;
 
    {
        auto start_time = std::chrono::steady_clock::now();
        multiplication_consistently(matrix, vx, vy, size);
 
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

        std::cout << "Time#1: " << elapsed_ns.count() << " ns\n";

        yvector_norm = function_yvector_norm(vy, size);
        std::cout << "Vector<y> norm: " << yvector_norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    std::cout << "Parallel, 2 threads" << std::endl;

    {
        auto start_time = std::chrono::steady_clock::now();
        multiplication_parallel2(matrix, vx, vy, size);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

        std::cout << "Time#2: " << elapsed_ns.count() << " ns\n";

        yvector_norm = function_yvector_norm(vy, size);
        std::cout << "Vector<y> norm: " << yvector_norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    std::cout << "Parallel, 4 threads" << std::endl;

    {
        auto start_time = std::chrono::steady_clock::now();
        multiplication_parallel4(matrix, vx, vy, size);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

        std::cout << "Time#3: " << elapsed_ns.count() << " ns\n";

        yvector_norm = function_yvector_norm(vy, size);
        std::cout << "Vector<y> norm: " << yvector_norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    std::cout << "Parallel, 6 threads" << std::endl;

    {
        auto start_time = std::chrono::steady_clock::now();
        multiplication_parallel6(matrix, vx, vy, size);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

        std::cout << "Time#4: " << elapsed_ns.count() << " ns\n";

        yvector_norm = function_yvector_norm(vy, size);
        std::cout << "Vector<y> norm: " << yvector_norm << std::endl;
    }

    std::cout << "--------------" << std::endl;

    delete[] vx, vy;

    if (matrix)
    {
        delete[] matrix;
        matrix = NULL;
    }

    return 0;
}
