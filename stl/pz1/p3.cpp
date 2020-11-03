#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    // Create base vector with child vectors,
    // iter and temp variables
    vector<vector<int>> vectors;
    size_t num; 
    int value;

    cout << "Wait for input (vec, value):" << endl;
    // Fill vectors
    cin >> num >> value;
    while (num != 0 || value != 0)
    {
        if (num >= vectors.size()) 
            vectors.resize(num + 1);

        vectors[num].push_back(value);

        cin >> num >> value;
    }

    // Start sorting and outputing if
    // we have at least one vector
    if (vectors.size() != 0)
    {
        // Sort vectors
        for (size_t i = 0; i < vectors.size(); i++)
            sort(vectors[i].begin(), vectors[i].end());

        cout << endl << "Vectors: " << endl;

        // Output vectors
        for (size_t i = 0; i < vectors.size(); i++)
        {
            if (!vectors[i].empty())
            {
                cout << i << ":\t";

                for (size_t ii = 0; ii < (vectors[i]).size(); ii++)
                    cout << vectors[i][ii] << "\t";

                cout << endl;
            }
        }
    }
    else
    {
        cout << "There is no vectors" << endl;
    }

    return 0;
}
