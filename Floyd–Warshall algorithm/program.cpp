#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

void create_transitive_closure_singlethreaded(bool** matrix, unsigned short size);
void create_transitive_closure_multithreaded(bool** matrix, unsigned short size);
double get_readable_time(struct timespec *start, struct timespec *finish);


int main()
{
    // Time
    struct timespec cl_start, cl_end;

    cout << "Write filename: ";

    string filename;
    cin >> filename;

    ifstream fin(filename);

    short output_matrices;
    cout << "\nWrite 0 if you want to output matrices" << endl;
    cout << "or any another to hide them: ";

    cin >> output_matrices;

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
    if (output_matrices == 0)
    {
        cout << "\nFilled matrix: " << endl;
        for (unsigned short y = 0; y < size_vertexes; y++)
        {
            for (unsigned short x = 0; x < size_vertexes; x++)
                if (matrix[x][y]) cout << "1 ";
                else cout << "0 ";
            cout << endl;
        }
    }

    // Create transitive closure
    cout << endl << "Write 0 if you want to run programm in single thread" << endl;
    cout << "or any another if you want to run programm in several: ";

    int i;
    cin >> i;

    clock_gettime(CLOCK_REALTIME, &cl_start);

    if (i == 0) create_transitive_closure_singlethreaded(matrix, size_vertexes);
    else  create_transitive_closure_multithreaded(matrix, size_vertexes);

    clock_gettime(CLOCK_REALTIME, &cl_end);
    cout << fixed << setprecision(6) << get_readable_time(&cl_start, &cl_end) << " sec." << endl;

    // Output transitive closure
    if (output_matrices == 0)
    {
        cout << "\nTransitive closure matrix:" << endl;
        for (unsigned short y = 0; y < size_vertexes; y++)
        {
            for (unsigned short x = 0; x < size_vertexes; x++)
                if (matrix[x][y]) cout << "1 ";
                else cout << "0 ";
            cout << endl;
        }
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


void create_transitive_closure_multithreaded(bool** matrix, unsigned short size)
{
    for (unsigned short i = 0; i < size; i++)
#pragma omp parallel num_threads(4)
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
