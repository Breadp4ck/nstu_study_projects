#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

void create_transitive_closure_singlethreaded(bool** matrix, unsigned short size);
void create_transitive_closure_multithreaded(bool** matrix, unsigned short size, int threads);
double get_readable_time(struct timespec *start, struct timespec *finish);
void output_matrix(bool** matrix, unsigned short size);


int main()
{
    // Time
    struct timespec cl_start, cl_end;

    cout << "Write filename: ";

    string input;
    cin >> input;

    ifstream fin(input);

    bool output_matrices;
    cout << "\nDo you want to output matrices? (y/n): ";

    cin >> input;
    if (input == "y") output_matrices = true;
    else if (input == "n") output_matrices = false;
    else throw "PROGRAM IS SHUTTING DOWN!!!";

    unsigned short size_vertexes, size_edges;
    unsigned short temp;
    fin >> size_vertexes >> size_edges;

    // Create empty matrix
    bool** matrix = new bool*[size_vertexes];
    for (unsigned short i = 0; i < size_vertexes; i++)
        matrix[i] = new bool[size_vertexes];

    // Fill matrix
    unsigned short vert_from, vert_to;
    for (unsigned short i = 0; i < size_edges; i++)
    {
        fin >> temp >> vert_from >> vert_to;
        matrix[vert_to-1][vert_from-1] = true;
    }    

    // Output matrix
    if (output_matrices)
    {
        cout << "\nFilled matrix: " << endl;
        output_matrix(matrix, size_vertexes);
    }

    // Create transitive closure
    cout << endl << "How many threads you want to use? (single/several): ";

    cin >> input;


    if (input == "single")
    {
        clock_gettime(CLOCK_REALTIME, &cl_start);
        create_transitive_closure_singlethreaded(matrix, size_vertexes);
    }
    else if (input == "several")
    {
        int threads_number;

        cout << "\nWrite count of threads: ";
        cin >> threads_number;

        clock_gettime(CLOCK_REALTIME, &cl_start);
        create_transitive_closure_multithreaded(matrix, size_vertexes, threads_number);
    }
    else
    {
        throw "PROGRAM IS SHUTTING DOWN!!!";
    }

    clock_gettime(CLOCK_REALTIME, &cl_end);
    cout << "\nTime: ";
    cout << fixed << setprecision(6) << get_readable_time(&cl_start, &cl_end) << " sec." << endl;

    // Output transitive closure
    if (output_matrices)
    {
        cout << "\nTransitive closure matrix:" << endl;
        output_matrix(matrix, size_vertexes);
    }

    return 0;
}


void create_transitive_closure_singlethreaded(bool** matrix, unsigned short size)
{
    for (unsigned short i = 0; i < size; i++)
        for (unsigned short s = 0; s < size; s++)
            for (unsigned short t = 0; t < size; t++)
                if (matrix[s][i] && matrix[i][t]) matrix[s][t] = true;
}


void create_transitive_closure_multithreaded(bool** matrix, unsigned short size, int threads)
{
    for (unsigned short i = 0; i < size; i++)
#pragma omp parallel num_threads(threads)
#pragma omp for
        for (unsigned short s = 0; s < size; s++)
            for (unsigned short t = 0; t < size; t++)
                if (matrix[s][i] && matrix[i][t]) matrix[s][t] = true;
}


double get_readable_time(struct timespec *start, struct timespec *finish)
{
    long int sec = finish->tv_sec - start->tv_sec;
    long int ns = finish->tv_nsec - start->tv_nsec;
    return sec + (double) ns / 1000000000;
}


void output_matrix(bool** matrix, unsigned short size)
{
    for (unsigned short y = 0; y < size; y++)
    {
        for (unsigned short x = 0; x < size; x++)
            if (matrix[x][y]) cout << "1 ";
            else cout << "0 ";
        cout << endl;
    }
}
