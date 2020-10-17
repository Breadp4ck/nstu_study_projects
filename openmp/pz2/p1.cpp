#include <chrono>
#include <omp.h>
#include <iostream>

const long long  SIZE = 100000;

double consecutive_sum(double* vx, double* vy, long long size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
        sum +=vx[i] * vy[i];

    return sum;
}

double parallel_sum2(double* vx, double* vy, long long size)
{
    double sum = 0;
    int i = 0;

#pragma omp parallel for shared(i) schedule(static, 10) reduction (+: sum) num_threads(2)
    for (i = 0; i < size; i++)
        sum += vx[i] * vy[i];

    return sum;
}

double parallel_sum4(double* vx, double* vy, long long size)
{
    double sum = 0;
    int i = 0;

#pragma omp parallel for shared(i) schedule(static, 10) reduction (+: sum) num_threads(4)
    for (i = 0; i < size; i++)
        sum += vx[i] * vy[i];

    return sum;
}

double parallel_sum6(double* vx, double* vy, long long size)
{
    double sum = 0;
    int i = 0;

#pragma omp parallel for shared(i) schedule(static, 10) reduction (+: sum) num_threads(6)
    for (i = 0; i < size; i++)
        sum += vx[i] * vy[i];

    return sum;
}

int main()
{
    double* vx = new double[SIZE];
    double* vy = new double[SIZE];
    double sum = 0;
    long long size;

    std::cout << "Size: ";
    std::cin >> size;

    std::cout << "--------------" << std::endl;

    for (int i = 0; i < size; i++)
    {
        vx[i] = rand() % 10;
        vy[i] = rand() % 10;
    }

    {
        auto start_time = std::chrono::steady_clock::now();
        sum = consecutive_sum(vx, vy, size);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        std::cout << "Consistently" << std::endl;
        std::cout << "Sum#1: " << sum << std::endl;
        std::cout << "Time#1: " << elapsed_ns.count() << " ns\n";
    }

    std::cout << "--------------" << std::endl;
    sum = 0;

    {
        auto start_time = std::chrono::steady_clock::now();
        sum = parallel_sum2(vx, vy, size);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        std::cout << "Parallel" << std::endl;
        std::cout << "Sum#2: " << sum << std::endl;
        std::cout << "Time#2: " << elapsed_ns.count() << " ns\n";
    }

    std::cout << "--------------" << std::endl;
    sum = 0;

    {
        auto start_time = std::chrono::steady_clock::now();
        sum = parallel_sum4(vx, vy, size);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        std::cout << "Parallel" << std::endl;
        std::cout << "Sum#3: " << sum << std::endl;
        std::cout << "Time#3: " << elapsed_ns.count() << " ns\n";
    }

    std::cout << "--------------" << std::endl;
    sum = 0;

    {
        auto start_time = std::chrono::steady_clock::now();
        sum = parallel_sum6(vx, vy, size);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        std::cout << "Parallel" << std::endl;
        std::cout << "Sum#4: " << sum << std::endl;
        std::cout << "Time#4: " << elapsed_ns.count() << " ns\n";
    }

    std::cout << "--------------" << std::endl;

    delete[] vx, vy;

    return 0;
}
